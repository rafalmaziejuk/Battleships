#pragma once

#include <SFML/Network.hpp>
#include <atomic>
#include <iostream>
#include <mutex>

namespace States
{
	class State;
}

class World;

namespace Net
{
    static std::mutex mutex;

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
        MISS,
        HIT_PART,
        HIT_ONE,
        HIT_AND_SANK,
        LOSE,
        REPLAY
    };

    void decode_status(sf::Socket::Status status);
    void decode_action(PlayerAction action);

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
        States::State* mGameState;

        bool mIsRunning;
        bool mIsConnectedWithRemote;

        bool mGameOver;
        bool mPlayAgain;
        bool mIsWon;
        bool mMyTurn;
        bool mReady;
        bool mEnemyReady;
        bool mGameStarted;
        bool mIStartedGame;
        bool mEnemyKnowsThatImReady;
        bool mEnemyKnowsThatIWantReplay;
        bool mReplay;
        bool mEnemyWantsReplay;
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
            mSankShips(0),
            mEnemyKnowsThatImReady(false),
            mEnemyKnowsThatIWantReplay(false),
            mReplay(true),
            mEnemyWantsReplay(true)
        {
        }
        ~Remote()
        {
        }

        void handle_missile(World& world, sf::Vector2i coord);
        void handle_message(message msg);

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
