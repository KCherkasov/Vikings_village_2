#ifndef DEDICATED_GAME_SERVER_H
#define DEDICATED_GAME_SERVER_H

// basic dedicated server functionality without any packets processing logic

#include "UDPSocket.h"
#include <unordered_map>
#include <queue>

#define MESSAGES_PER_SOCKET 5 // maximal number of messages read from each socket per one loop iteration

class DedicatedGameServer {
  public:
    DedicatedGameServer() { initialize_sockets(); }
    virtual ~DedicatedGameServer() { shutdown_sockets(); }
    bool open_socket(unsigned short port = 0);
    void close_socket();
    void add_listener(const Address& listener);
    void remove_listener(size_t address, unsigned short port);
    bool send_message(size_t address, unsigned short port, const void* message, size_t message_size);
    bool broadcast_message(const void* message, size_t message_size);
    void add_packet(RawPacket* packet); // add an out packet
  protected:
    void receive_messages();
    virtual void process_packets() {}

    UDPSocket _socket;
    mutable std::unordered_map<std::string, Address> _listeners;
    mutable std::queue<RawPacket*> _packets_in;
    mutable std::queue<RawPacket*> _packets_out;
    mutable std::queue<BaseCommand*> _processed_packets;
  private:
    size_t _packet_id;
    size_t _ack;
};

#endif
