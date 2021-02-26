#pragma once

#include <SFML/Network.hpp>

enum class RemoteType
{
	SERVER, CLIENT
};

class Remote
{

public:
    sf::TcpSocket mSocket;
    sf::Packet mPacketSent;
    sf::Packet mPacketReceived;
    bool mIsRunning;
    bool mIsConnectedWithRemote;

    Remote()
        : mSocket(), 
          mPacketSent(), 
          mPacketReceived(),
          mIsRunning(false),
          mIsConnectedWithRemote(false) 
    {
    }
    ~Remote() 
    {
    }

    inline bool is_connected_with_remote(void) const
    {
        return mIsConnectedWithRemote;
    }

    inline bool is_running(void) const
    {
        return mIsRunning;
    }

};


