#include "DedicatedGameServer.h"

bool DedicatedGameServer::add_socket(unsigned short port) {
  if (this->_socket.is_open()) {
    printf("the socket is already opened at the port %d.\n", this->_socket.port());
    return false;
  }
  return this->_socket.open(port);
}

void DedicatedGameServer::close_socket() {
  if (!this->_socket.is_open()) {
    printf("the socket is already closed.\n");
    return;
  }
  this->_socket.close();
}

bool DedicatedGameServer::add_listener(const Address& address) {
  if (this->_listeners.count(address.key()) > 0) {
    printf("such listener already exists.\n");
    return false;
  }
  this->_listeners[address.key()] = address;
  return true;
}

void DedicatedGameServer::remove_listener(const std::string& key) {
  if (this->_listeners.count(key) == 0) {
    printf("no such listener.\n");
    return;
  }
  this->_listeners.erase(key);
}

void DedicatedGameServer::remove_listener(size_t address, unsigned short port) {
  std::ostringstream buffer;
  buffer << address;
  std::string key = buffer.str();
  key.append(":");
  buffer.clear();
  buffer << port;
  key += buffer.str();
  this->remove_listener(key);
}
