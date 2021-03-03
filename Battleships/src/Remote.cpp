#include "Remote.h"
#include "GameState.h"

namespace Net
{
    void decode_status(sf::Socket::Status status)
    {
        switch (status)
        {
            case sf::Socket::Done:          std::cout << "\nDONE";              break;
            case sf::Socket::NotReady:      std::cout << "\nNOTREADY";          break;
            case sf::Socket::Partial:       std::cout << "\nPARTIAL";           break;
            case sf::Socket::Disconnected:  std::cout << "\nDISCONNECTED";      break;
            case sf::Socket::Error:         std::cout << "\nERROR";             break;
        }
    }

    void decode_message(MessageCode msgCode)
    {
        switch (msgCode)
        {
            case MessageCode::NUL:             std::cout << "NUL\n";           break;
            case MessageCode::DISCONNECT:      std::cout << "DISCONNECT\n";    break;
            case MessageCode::MISSILE:         std::cout << "MISSILE\n";       break;
            case MessageCode::READY:           std::cout << "READY\n";         break;
            case MessageCode::MISS:            std::cout << "MISS\n";          break;
            case MessageCode::HIT_PART:        std::cout << "HIT_PART\n";      break;
            case MessageCode::HIT_ONE:         std::cout << "HIT_ONE\n";       break;
            case MessageCode::HIT_AND_SANK:    std::cout << "HIT_AND_SANK\n";  break;
        }
    }

    void Remote::set_game_state(States::State* state)
    {
        mGameState = state;
    }

    void Remote::wait_till_game_state_ran(void)
    {
        // after this loop GameState pointer is set up correctly so that class attributes can be used
        while (mGameState == nullptr) {}
    }

    void Remote::set_up_for_new_game(bool isWon)
    {
        mGameOver = true;
        mGameStarted = false;
        mIsWon = false;
        mReady = false;
        mEnemyReady = false;
        mEnemyKnowsThatImReady = false;
        mEnemyKnowsThatIWantReplay = false;
        mReplay = false;
        mEnemyWantsReplay = false;
        mSankShips = 0;

        if (mIStartedGame)
        {
            mMyTurn = false;
            mIStartedGame = false;
        }
        else
        {
            mMyTurn = true;
            mIStartedGame = true;
        }
        static_cast<States::GameState*>(mGameState)->get_world().update_game_status(isWon);
        static_cast<States::GameState*>(mGameState)->update_ready_button_text("Replay");
        static_cast<States::GameState*>(mGameState)->activate_ready_button();
    }

    void Remote::try_receive(void)
    {
        sf::Socket::Status status;
        size_t received;

        if ((status = mSocket.receive(&mMsgReceived, sizeof(message), received)) == sf::Socket::Done)
        {
            std::cout << "Data received! \n";
            //decode_status(status);
            handle_message(mMsgReceived);
        }
        else if (status == sf::Socket::Disconnected || status == sf::Socket::Error)
        {
            mIsConnectedWithRemote = false;
            std::cout << "Disconnected with remote or an error occured\n";
        }
        else
        {
            //decode_status(status);
        }
    }

    void Remote::try_send(void)
    {
        
        if (both_want_replay_and_i_am_ready())
        {
            send_message(MessageCode::READY);
            mEnemyKnowsThatImReady = true;
            
        }
        else if (i_want_replay())
        {
            send_message(MessageCode::REPLAY);
            mEnemyKnowsThatIWantReplay = true;       
        }
        else if (both_clicked_replay())
        {
            static_cast<States::GameState*>(mGameState)->reset_game();
        }

        if (both_ready())
        {
            if (!mGameStarted)
            {
                //std::cout << "Im ready and enemy is ready too!";
                static_cast<States::GameState*>(mGameState)->deactivate_ready_button();
                static_cast<States::GameState*>(mGameState)->get_world().get_enemy_grid().mShipHint.set_all_hints_active();
                mGameStarted = true;
                mGameOver = false;
            }
            if (!mMsgSent.is_clear())
            {
                send_message();
            }
        }
    }

    void Remote::send_message(MessageCode msgCode)
    {
        sf::Socket::Status status;
        size_t sent;

        mMsgSent.ID = msgCode;
        if ((status = mSocket.send(&mMsgSent, sizeof(mMsgSent), sent)) != sf::Socket::Done)
            decode_status(status);
        else
        {
            //decode_message(msgCode);
        }
        mMsgSent.clear();
    }

    void Remote::send_message(void)
    {
        sf::Socket::Status status;
        size_t sent;

        if ((status = mSocket.send(&mMsgSent, sizeof(mMsgSent), sent)) != sf::Socket::Done)
            decode_status(status);
        else
        {
            //decode_message(msgCode);
        }
        mMsgSent.clear();
    }

    void Remote::handle_message(message msg)
    {
        std::cout << "msgID (" << (int)msg.ID << ")\n";
        //sf::Socket::Status status;
        //size_t sent;
        World& world = static_cast<States::GameState*>(mGameState)->get_world();

        switch (msg.ID)
        {
        case MessageCode::REPLAY:
            mEnemyWantsReplay = true;

            break;
        case MessageCode::HIT_PART:
            //std::cout << "Ship is hit!";
            world.get_enemy_grid().handle_missile_hit(MessageCode::HIT_PART,mRecentlyFiredMissile);
            world.activate_enemy_grid(true);
            std::cout << "\n";
            break;
        case MessageCode::HIT_ONE:
            //std::cout << "Ship is hit!";
            world.get_enemy_grid().handle_missile_hit(MessageCode::HIT_ONE, mRecentlyFiredMissile);
            world.activate_enemy_grid(true);
            break;
        case MessageCode::HIT_AND_SANK:
            //std::cout << "Ship is hit!";
            world.get_enemy_grid().handle_missile_hit(MessageCode::HIT_AND_SANK, mRecentlyFiredMissile);
            world.activate_enemy_grid(true);
            break;
        case MessageCode::MISS:
            //std::cout << "You missed! :( ";
            world.get_enemy_grid().handle_miss(mRecentlyFiredMissile);
            world.activate_enemy_grid(false);
            break;
        case MessageCode::NUL:
            //std::cout << "NUL";
            break;
        case MessageCode::READY:
            //std::cout << "READY";
            mEnemyReady = true;
            break;
        case MessageCode::MISSILE:
        {
            //std::cout << "Odebralem -  " << msg.coord.x << " " << msg.coord.y;
            handle_missile_msg(world, msg.coord);
            world.activate_enemy_grid(true);
            break;
        }
        case MessageCode::DISCONNECT:
            mIsConnectedWithRemote = false;
            break;
        case MessageCode::LOSE:
            world.get_enemy_grid().mShotTiles[mRecentlyFiredMissile.x][mRecentlyFiredMissile.y] = TileStatus::HIT;
            world.get_enemy_grid().update_shot_tiles(MessageCode::HIT_AND_SANK, mRecentlyFiredMissile);
            set_up_for_new_game(true);
            //std::cout << "You won!";
            break;
        }
    }

    void Remote::handle_missile_msg(World& world, sf::Vector2i coord)
    {
        world.handle_missile(coord);
    }

    bool Remote::is_connected_with_remote(void) const
    {
        return mIsConnectedWithRemote;
    }

    bool Remote::is_running(void) const
    {
        return mIsRunning;
    }

    // in the first party, both mReplay and mEnemyWantsReplay are set to true
    bool Remote::both_want_replay_and_i_am_ready(void) const
    {
        return (mReplay && mEnemyWantsReplay && mReady && !mEnemyKnowsThatImReady) ? true : false;
    }

    bool Remote::i_want_replay(void) const
    {
        return (mReplay && !mEnemyKnowsThatIWantReplay) ? true : false;
    }

    bool Remote::both_clicked_replay(void) const
    {
        return (mReplay && mEnemyWantsReplay && !mGameStarted && mGameOver) ? true : false;
    }

    bool Remote::both_ready(void) const
    {
        return (mReady && mEnemyReady) ? true : false;
    }

    void Remote::check_connection_status(void)
    {
        if (!mIsConnectedWithRemote)
            static_cast<States::GameState*>(mGameState)->mExitToMenuState = true;
    }

}