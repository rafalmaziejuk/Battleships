#pragma once

#include <SFML/Network.hpp>
#include <atomic>
#include <iostream>

enum class RemoteType
{
	SERVER, CLIENT
};



class Remote
{

public:
    std::atomic_bool mDone;
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
        mIsConnectedWithRemote(false),
        mDone(false)
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


