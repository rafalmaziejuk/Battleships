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

    bool mGameOver;
    bool mPlayAgain;
    bool mIsWon;
    bool mMyTurn;
    bool mReady;

    Remote()
        : mSocket(),
        mPacketSent(),
        mPacketReceived(),
        mIsRunning(false),
        mIsConnectedWithRemote(false),
        mDone(false),
        mGameOver(false),
        mPlayAgain(false),
        mIsWon(false),
        mMyTurn(false),
        mReady(false)
    {
    }
    ~Remote() 
    {
    }

    /*
    inline bool game_over(void) const               {   return (mGameOver) ? true : false;  }
    inline bool want_to_play_again(void) const      {   return (mPlayAgain) ? true : false; }
    inline bool is_game_won(void) const             {   return (mIsWon) ? true : false;     }
    inline bool is_my_turn(void) const              {   return (mMyTurn) ? true : false;    }
    inline bool is_ready(void) const                {   return (mReady) ? true : false;     }
    */
    

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


