#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

// based on materials from gafferongames.com

#define PLATFORM_WINDOWS 1
#define PLATFORM_MAC 2
#define PLATFORM_LINUX 3

#if defined(_WIN32)
  #define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
  #define PLATFORM PLATFORM_MAC
#else
  #define PLATFORM PLATFORM_LINUX
#endif

#if PLATFORM == PLATFORM_WINDOWS
  #include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_LINUX
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <fcntl.h>
#endif

#include <string>
#include <cstring>

const size_t GAME_PROTOCOL_ID = 34280012;

// some tricks to enable socket-layer functionality on Windows
// on unix-like platforms those functions do nothing

bool initialize_sockets() {
  #if PLATFORM == PLATFORM_WINDOWS
    WSADATA wsa_data;
    return WSAStartup(MAKEWORD(2, 2), &wsa_data) == NO_ERROR;
  #else
    return true;
  #endif
}

void shutdown_sockets() {
  #if PLATFORM == PLATFORM_WINDOWS
    WSACleanup();
  #endif
}

class Address {
  public:
    Address(): _address(0), _port(0) { this->_own_id = ++this->_id; }
    Address(size_t address, unsigned short port): _address(address), _port(port) { this->_own_id = ++this->_id; } // to initialize as address:port
    Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port); // to initialize address as a.b.c.d:port
    ~Address() {}
    size_t address() const { return this->_address; }
    void set_address(size_t address) { this->_address = address; }
    unsigned short port() const { return this->_port; }
    void set_port(unsigned short port) { this->_port = port; }
    std::string key() const;
  private:
    size_t _address;
    unsigned short _port;
};

#define DEFAULT_HANDLE -1
#define DEFAULT_PORT 0

class UDPSocket {
  public:
    UDPSocket(): _handle(DEFAULT_HANDLE) {}
    ~UDPSocket() {}
    bool open(unsigned short port = 0);
    void close();
    bool is_open() const;
    bool send(const Address& destination, const void* data, ssize_t size);
    int receive(Address& sender, void* data, ssize_t size);
    unsigned short port() const { return this->_port; }
  private:
    ssize_t _handle;
    unsigned short _port;
};

// raw packet that's being send between server and clients
// first 4 bytes are reserved for protocol_id, next 4 bytes are for packet_id
// third 4 bytes are for ack sequence, then go 4 bytes of message size and
// message itself

enum PacketHeaders { PH_PROTOCOL_ID, PH_PACKET_ID, PH_ACK, PH_SIZE };

class RawPacket {
  public:
    RawPacket(): _message(NULL) {}
    RawPacket(const Address& address, char* message): _address(address), _message(message) {}
    ~RawPacket() { delete[] this->_message; }
    size_t protocol_id() const;
    size_t packet_id() const;
    size_t ack() const;
    size_t length() const;
    char* data() const;
    bool has_headers() const;
    void add_headers();
    void strip_headers()
    bool set_header(size_t header value, size_t header_id);
    Address& address() const { return this->_address; }
    Address _address;
    char* _message;
};

#endif
