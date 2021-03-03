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

    enum class MessageCode
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
    void decode_message(MessageCode action);

    struct message
    {
        MessageCode ID;
        sf::Vector2i coord;

        message() : ID(MessageCode::NUL), coord(sf::Vector2i(-1, -1)) 
        {
        }
        
        void clear(void)
        {
            ID = MessageCode::NUL;
            coord = sf::Vector2i(0, 0);
        }

        bool is_clear(void)
        {
            return (ID == MessageCode::NUL) ? true : false;
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

        void set_game_state(States::State* state);
        void wait_till_game_state_ran(void);
        void set_up_for_new_game(bool isWon);

        void try_receive(void);
        void try_send(void);
        void send_message(MessageCode action);
        void send_message(void);

        void handle_missile_msg(World& world, sf::Vector2i coord);
        void handle_message(message msg);

        virtual void start(void) = 0;
        virtual void stop(void) = 0;

        /* boolean expressions */

        bool is_connected_with_remote(void) const;
        bool is_running(void) const;
        bool both_want_replay_and_i_am_ready(void) const;   // in the first party, both mReplay and mEnemyWantsReplay are set to true
        bool i_want_replay(void) const;
        bool both_clicked_replay(void) const;
        bool both_ready(void) const;

        void check_connection_status(void);
    };

}
