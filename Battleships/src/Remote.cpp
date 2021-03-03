#include "Remote.h"
#include "GameState.h"

namespace Net
{
    void decode_status(sf::Socket::Status status)
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

    void decode_action(PlayerAction action)
    {
        switch (action)
        {
            case PlayerAction::NUL: std::cout << "NUL\n";                   break;
            case PlayerAction::DISCONNECT: std::cout << "DISCONNECT\n";     break;
            case PlayerAction::MISSILE: std::cout << "MISSILE\n";           break;
            case PlayerAction::READY: std::cout << "READY\n";               break;
            case PlayerAction::MISS: std::cout << "MISS\n";                 break;
            case PlayerAction::HIT_PART: std::cout << "HIT_PART\n";         break;
            case PlayerAction::HIT_ONE: std::cout << "HIT_ONE\n";           break;
            case PlayerAction::HIT_AND_SANK: std::cout << "HIT_AND_SANK\n"; break;
        }
    }

    void Remote::handle_missile(World& world, sf::Vector2i coord)
    {
        // if missile hits a ship then its pointer is returned
        Ship* ship = world.is_ship_choosen(coord);

        sf::Socket::Status status;
        size_t sent;

        mMsgSent.clear();

        if (ship == nullptr) // if pointer is nullptr then remote missed
        {
            std::cout << "Enemy missed !\n";

            // updating position to draw a dot
            world.get_player_grid().mShotTiles[coord.x][coord.y] = TileStatus::MISS;

            // setting data for feedback message
            mMsgSent.ID = PlayerAction::MISS;

            mMyTurn = true;
            world.activate_enemy_grid(true);
        }
        else
        {
            std::cout << "Enemy hit your ship!\n";

            ////////////////////////////////////////
            //world.get_player_grid().update_shot_tiles(ship, coord);
            //mMsgSent.ID = PlayerAction::HIT;
            /// /////////////////////////////////////
            // the above should be changed to this : ///////

            mMsgSent.ID = world.get_player_grid().update_shot_tiles(ship, coord);
            // and returned ID should be handled properly in remote's handle_message()
            /////////////////////////////////////////
            if (mMsgSent.ID == PlayerAction::LOSE)
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
                static_cast<States::GameState*>(mGameState)->get_world().update_game_status(false);
                static_cast<States::GameState*>(mGameState)->update_ready_button_text("Replay");
                static_cast<States::GameState*>(mGameState)->activate_ready_button();
            }
            else
            {
                mMyTurn = false;
                world.activate_enemy_grid(false);
            }
        }
        //sending feedback message to remote 
        if ((status = mSocket.send(&mMsgSent, sizeof(mMsgSent), sent)) != sf::Socket::Done)
            decode_status(status);
        else
        {
            std::cout << "I sent information about missile accuracy to remote!\n";
        }
        // clearing message struct
        mMsgSent.clear();

        //std::cout << "Enemy hit your ship!\n";
    }

    void Remote::handle_message(message msg)
    {
        std::cout << "msgID (" << (int)msg.ID << ")\n";
        //sf::Socket::Status status;
        //size_t sent;
        World& world = static_cast<States::GameState*>(mGameState)->get_world();

        switch (msg.ID)
        {
        case PlayerAction::REPLAY:
            mEnemyWantsReplay = true;

            break;
        case PlayerAction::HIT_PART:
            std::cout << "Ship is hit!";
            world.get_enemy_grid().mShotTiles[mRecentlyFiredMissile.x][mRecentlyFiredMissile.y] = TileStatus::HIT;
            world.get_enemy_grid().update_shot_tiles(PlayerAction::HIT_PART, mRecentlyFiredMissile);
            mMyTurn = true;
            world.activate_enemy_grid(true);
            std::cout << "\n";
            break;
            // above HIT handler should be separated to this : 
            //////////////////////////////////////
        case PlayerAction::HIT_ONE:

            std::cout << "Ship is hit!";
            world.get_enemy_grid().mShotTiles[mRecentlyFiredMissile.x][mRecentlyFiredMissile.y] = TileStatus::HIT;
            world.get_enemy_grid().update_shot_tiles(PlayerAction::HIT_ONE, mRecentlyFiredMissile);
            mMyTurn = true;
            world.activate_enemy_grid(true);

            break;
        case PlayerAction::HIT_AND_SANK:
            std::cout << "Ship is hit!";
            world.get_enemy_grid().mShotTiles[mRecentlyFiredMissile.x][mRecentlyFiredMissile.y] = TileStatus::HIT;
            world.get_enemy_grid().update_shot_tiles(PlayerAction::HIT_AND_SANK, mRecentlyFiredMissile);
            mMyTurn = true;
            world.activate_enemy_grid(true);
            break;
            ///////////////////////////////////////

        case PlayerAction::MISS:
            std::cout << "You missed! :( ";
            world.get_enemy_grid().mShotTiles[mRecentlyFiredMissile.x][mRecentlyFiredMissile.y] = TileStatus::MISS;
            world.activate_enemy_grid(false);
            mMyTurn = false;
            std::cout << "\n";
            break;
        case PlayerAction::NUL:
            std::cout << "NUL";
            break;
        case PlayerAction::READY:
            std::cout << "READY";
            mEnemyReady = true;
            break;
        case PlayerAction::MISSILE:
        {
            std::cout << "Odebralem -  " << msg.coord.x << " " << msg.coord.y;

            handle_missile(world, msg.coord);
            world.activate_enemy_grid(true);

            break;
        }
        case PlayerAction::DISCONNECT:
            std::cout << "DISCONNECT";
            break;
        case PlayerAction::LOSE:
            world.get_enemy_grid().mShotTiles[mRecentlyFiredMissile.x][mRecentlyFiredMissile.y] = TileStatus::HIT;
            world.get_enemy_grid().update_shot_tiles(PlayerAction::HIT_AND_SANK, mRecentlyFiredMissile);

            mGameOver = true;
            mGameStarted = false;
            mIsWon = true;
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
            static_cast<States::GameState*>(mGameState)->get_world().update_game_status(true);
            static_cast<States::GameState*>(mGameState)->update_ready_button_text("Replay");
            static_cast<States::GameState*>(mGameState)->activate_ready_button();
            std::cout << "You won!";
            break;
        }

    }

}