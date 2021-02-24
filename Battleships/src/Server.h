#pragma once

#include <iostream>
#include <SFML/Network.hpp>
#include <thread>

enum class RemoteType
{
    SERVER, CLIENT
};

class Server
{
private:
    sf::TcpListener mListener;
    sf::TcpSocket mSocket;
    sf::Packet mPacketSent;
    sf::Packet mPacketReceived;
    std::thread* mServerThread;
    bool mIsRunning;
    bool mIsConnectedWithRemote;
    unsigned mPort;
    void run_server(void);

public:
    Server();
    ~Server();

    bool is_connected_with_remote(void) const;
    bool is_running(void) const;
    void set_port(const int port);
    void start(void);


};
