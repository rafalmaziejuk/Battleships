#pragma once

#include <SFML/Network.hpp>
#include <atomic>
#include <iostream>
#include <mutex>


namespace Net
{
    
    static std::mutex mutex;    // not sure if it is a good solution (to be change?)

    void decode_status(sf::Socket::Status status);

    enum class RemoteType
    {
        SERVER, CLIENT
    };

    enum class PlayerAction
    {
        NUL,
        DISCONNECT,
        MISSILE,
        READY,
        HIT,
        MISS,
        HIT_ONE,
        HIT_VERTICAL_SHIP,
        HIT_HORIZONTAL_SHIP,
        HIT_AND_SANK
    };

    struct message
    {
        PlayerAction ID;
        sf::Vector2i coord;

        message() : ID(PlayerAction::NUL), coord(sf::Vector2i(-1, -1)) 
        {
        }
        
        void clear(void)
        {
            ID = PlayerAction::NUL;
            coord = sf::Vector2i(0, 0);
        }

        bool is_clear(void)
        {
            return (ID == PlayerAction::NUL) ? true : false;
        }
    };

    class Remote
    {
    private:

        virtual bool establish_connection(void) = 0;

    public:
        std::atomic_bool mDone;
        sf::TcpSocket mSocket;
        sf::Packet mPacketSent;
        sf::Packet mPacketReceived;
        message mMsgSent;
        message mMsgReceived;

        sf::Vector2i mRecentlyFiredMissile;
        bool mIsRunning;
        bool mIsConnectedWithRemote;

        bool mGameOver;
        bool mPlayAgain;
        bool mIsWon;
        bool mMyTurn;
        bool mReady;
        bool mEnemyReady;
        bool mGameStarted;

        unsigned mSankShips;

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
            mReady(false),
            mEnemyReady(false),
            mGameStarted(false),
            mSankShips(0)
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

}
