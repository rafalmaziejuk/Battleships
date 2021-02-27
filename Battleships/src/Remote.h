#pragma once

#include <SFML/Network.hpp>
#include <atomic>
#include <iostream>

enum class RemoteType
{
	SERVER, CLIENT
};

inline void decode_status(sf::Socket::Status status)
{
    switch (status)
    {
    case sf::Socket::Done:          std::cout << "\nDONE";            break;
    case sf::Socket::NotReady:      std::cout << "\nNOTREADY";        break;
    case sf::Socket::Partial:       std::cout << "\nPARTIAL";         break;
    case sf::Socket::Disconnected:  std::cout << "\nDISCONNECTED";    break;
    case sf::Socket::Error:         std::cout << "\nERROR";           break;
    }
}

class Remote
{
private:

    virtual bool establish_connection(void) = 0;

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

    virtual void start(void) = 0;
    virtual void stop(void) = 0;
    
};


