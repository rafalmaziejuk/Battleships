#pragma once

#include <SFML/Network.hpp>

class Client
{
private:
    sf::TcpListener mListener;
    sf::TcpSocket mSocket;
    sf::IpAddress mRemoteIp;
    sf::Packet mPacketSent;
    sf::Packet mPacketReceived;
    unsigned mPort;

public:
    Client();
    ~Client();

    void set_port(const int port);
    void set_ip(const sf::IpAddress ip);
    void run_client(void);
 
};
