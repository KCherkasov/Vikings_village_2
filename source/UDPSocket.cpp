#include "UDPSocket.h"
#include <cstdio>
#include <sstream>

const size_t MAX_BUFFER_SIZE = 256; // needs altering basing on largest package size
const ssize_t DEFAULT_ID = 0;


Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned int port): _address(0), _port(port) {
  this->_address = (a << 24) | (b << 16) | (c << 8) | d; // merging parts of IP-address into single one
  this->_own_id = ++this->_id;
}

std::string Address::key() const {
  std::ostringstream buffer;
  buffer << this->_address;
  std::string result = buffer.str();
  result.append(":");
  buffer.clear();
  buffer << this->_port;
  result += buffer.str();
  return result;
}

bool UDPSocket::open(unsigned short port) {
  this->_handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (this->_handle <= 0) {
    printf("failed to create socket\n");
    return false;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons((unsigned short) port);
  if (bind(this->_handle, (const sockaddr*) &address, sizeof(sockaddr_in)) < 0) {
    printf("failed to bind socket\n");
    this->close();
    return false;
  }
  #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_LINUX
    ssize_t non_blocking = 1;
    if (fcntl(this->_handle, F_SETFL, O_NONBLOCK, non_blocking) == -1) {
      printf("failed to set non-blocking\n");
      this->close();
      return false;
    }
  #elif PLATFORM == PLATFORM_WINDOWS
    DWORD non_blocking = 1;
    if (ioctl(this->_handle, FIONBIO, &non_blocking) != 0) {
      printf("failed to set non-blocking\n");
      this->close();
      return false;
    }
  #endif
  this->_port = port;
  return true;
}

bool UDPSocket::is_open() const {
  return this->_handle > 0 && this->_port != DEFAULT_PORT;
}

void UDPSocket::close() {
  #if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_LINUX
    close(this->_handle);
  #elif PLATFORM == PLATFORM_WINDOWS
    closesocket(this->_handle);
  #endif
}

bool UDPSocket::send(const Address& destination, const void* data, ssize_t size) {
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = htonl(destination.address());
  addr.sin_port = htons(destination.port());
  ssize_t sent_bytes = sendto(this->_handle, (const char*) data, size, 0, (sockaddr*) address, sizeof(sockaddr_in));
  if (sent_bytes != size) {
    return false;
  }
  return true;
}

int UDPSocket::receive(Address& sender, void* data, ssize_t size) {
  #if PLATFORM == PLATFORM_WINDOWS
    typedef int socklen_t;
  #endif
  sockaddr_in from;
  socklen_t from_size = sizeof(from);
  int bytes = recvfrom(this->_handle, (char*) data, MAX_BUFFER_SIZE, 0, (sockaddr*) &from, &from_size);
  sender.set_address(ntohl(from.sin_addr.s_addr));
  sender.set_port(ntohs(from.sin_port));
  return bytes;
}

size_t RawPacket::protocol_id() const {
  size_t protocol_id = 0;
  if (this->_message != NULL) {
    memcpy(&protocol_id, this->_message, sizeof(size_t));
  }
  return protocol_id;
}

size_t RawPacket::packet_id() const {
  size_t packet_id = 0;
  if (this->_message != NULL) {
    memcpy(&packet_id, this->_message + sizeof(size_t), sizeof(size_t));
  }
  return packet_id;
}

size_t RawPacket::ack() const {
  size_t ack = 0;
  if (this->_message != NULL) {
    memcpy(&ack, this->_message + sizeof(size_t) * 2, sizeof(size_t));
  }
  return ack;
}

char* RawPacket::data() const {
  char* data = this->_message;
  if (this->has_headers()) {
    data += sizeof(size_t) * 4;
  }
  return data;
}

bool RawPacket::has_headers() const {
  return this->protocol_id() == GAME_PROTOCOL_ID;
}

void RawPacket::add_headers() {
  const size_t DEFAULT_HEADER = 0;
  if (this->has_headers()) {
    return;
  }
  size_t pure_length = strlen(this->_message);
  char* buffer = new char[sizeof(size_t) * 4 + pure_length + 1];
  pure_length = htonl(pure_length);
  memcpy(buffer, &GAME_PROTOCOL_ID, sizeof(size_t));
  memcpy(buffer + sizeof(size_t), DEFAULT_HEADER, sizeof(size_t));
  memcpy(buffer + sizeof(size_t) * 2, DEFAULT_HEADER, sizeof(size_t));
  memcpy(buffer + sizeof(size_t) * 3, &pure_length, sizeof(size_t));
  strcpy(buffer + sizeof(size_t) * 4, this->_message);
  delete[] this->_message;
  this->_message = buffer;
}

void RawPacket::strip_headers() {
  if (!this->has_headers()) {
    return;
  }
  size_t pure_length = strlen(this->_message) - sizeof(size_t) * 4;
  char* buffer = new char[ pure_length + 1];
  memcpy(buffer, this->_message + sizeof(size_t) * 4, pure_length);
  delete[] this->_message;
  this->_message = buffer;
}

bool RawPacket::set_header(size_t header_value, size_t header_id) {
  if (!this->has_headers() || header_id >= PH_SIZE) {
    return false;
  }
  memcpy(this->_message + sizeof(size_t) * header_id, &header_value, sizeof(size_t));
  return true;
}
