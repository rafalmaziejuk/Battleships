#pragma once

#include <SFML/Network.hpp>

#include <thread>

class Client
{
private:
    sf::TcpListener mListener;
    sf::TcpSocket mSocket;
    sf::IpAddress mRemoteIp;
    sf::Packet mPacketSent;
    sf::Packet mPacketReceived;
    std::thread* mClientThread;
    bool mIsRunning;
    unsigned mPort;
    void run_client(void);
    bool mIsConnectedWithRemote;

public:
    Client();
    ~Client();

    bool is_connected_with_remote(void) const;
    bool is_running(void) const;
    void set_port(const int port);
    void set_ip(const sf::IpAddress ip);
    void start(void);

 
};
