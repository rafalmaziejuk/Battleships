#pragma once

#include <iostream>
#include <SFML/Network.hpp>

class Server
{
private:
    sf::TcpListener mListener;
    sf::TcpSocket mSocket;
    sf::Packet mPacketSent;
    sf::Packet mPacketReceived;

    unsigned mPort;

public:
    Server();
    ~Server();

    void set_port(const int port);
    void run_server(void);

};
