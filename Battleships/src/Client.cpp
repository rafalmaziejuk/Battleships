#include "Client.h"
#include <iostream>

namespace Net
{
    Client::Client()
        : Remote(), mPort(0), mClientThread(nullptr), mGameState(nullptr)
    {
        mMyTurn = false;
        mIStartedGame = false;
    }

    Client::~Client()
    {

    }

    void Client::set_game_state(States::State* state)
    {
        mGameState = state;
    }

    void Client::set_port(const int port)
    {
        mPort = port;
    }

    void Client::set_ip(sf::IpAddress ip)
    {
        mRemoteIp = ip;
    }

    void Client::start(void)
    {
        mClientThread = new std::thread(&Client::run_client, this);
        mIsRunning = true;
    }

    void Client::stop(void)
    {
        mIsRunning = false;
        mDone = true;
        mClientThread->join();
        delete mClientThread;
        mDone = false;
    }

    void Client::handle_missile(World& world, sf::Vector2i coord)
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

    void Client::update_grid(Grid& grid)
    {

    }

    void Client::handle_message(message msg)
    {
        std::cout << "msgID ("<<(int)msg.ID<<")\n";
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

    bool Client::establish_connection(void)
    {
        sf::Socket::Status status;

        std::cout << "Trying to connect with " << mRemoteIp << " on port " << mPort << "\n";

        // Connect to the server

        while (!mIsConnectedWithRemote)
        {
            status = mSocket.connect(mRemoteIp, mPort);
            //decode_status(status);
            if (status == sf::Socket::Done) // when this function returs a valid value it means that conection is established
            {
                std::cout << "Connected to server " << mRemoteIp << "\n";
                mIsConnectedWithRemote = true;
            }
            if (mDone)
            {
                if (mIsConnectedWithRemote)
                    mSocket.disconnect();
                return false;
            }
        }
        return true;
    }

    void Client::run_client(void)
    {
        sf::Socket::Status status;

        bool connectionStatus = establish_connection();
        if (!connectionStatus)
            return;

        // after this loop GameState pointer is set up correctly so that class attributes can be used
        while (mGameState == nullptr) {}

        mSocket.setBlocking(false);
        
        size_t received;
        size_t sent;



        while (!mDone)
        {

            // data exhange appears every 0,5 s
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            //std::cout << ".";

            mutex.lock();

            if ((status = mSocket.receive(&mMsgReceived, sizeof(message), received)) != sf::Socket::Done) {}
                //decode_status(status);
            else if (status == sf::Socket::Done)
            {
                std::cout << "Data received! \n";
                handle_message(mMsgReceived);
            }
            else if (status == sf::Socket::Disconnected)
            {
                // disconnected
                // end client
                // end state 
                // back to main menu
                std::cout << "Disconnected with remote or an error occured\n";
            }

            
            if (mReplay && mEnemyWantsReplay && mReady && !mEnemyKnowsThatImReady)
            {
                mMsgSent.ID = PlayerAction::READY;
                if ((status = mSocket.send(&mMsgSent, sizeof(mMsgSent), sent)) != sf::Socket::Done)
                    decode_status(status);
                else
                {
                    std::cout << "I sent information about being ready to battle!\n";
                    mEnemyKnowsThatImReady = true;
                }
            }
            else if (mReplay && !mEnemyKnowsThatIWantReplay)
            {
                mMsgSent.ID = PlayerAction::REPLAY;
                if ((status = mSocket.send(&mMsgSent, sizeof(mMsgSent), sent)) != sf::Socket::Done)
                    decode_status(status);
                else
                {
                    std::cout << "I sent information that you are willing to play again!\n";
                    mEnemyKnowsThatIWantReplay = true;
                }
            }
            else if (mReplay && mEnemyWantsReplay && !mGameStarted && mGameOver)
            {
                static_cast<States::GameState*>(mGameState)->update_ready_button_text("Ready");
                static_cast<States::GameState*>(mGameState)->get_world().reset_game();
                if(mMyTurn)
                    static_cast<States::GameState*>(mGameState)->get_world().activate_enemy_grid(true);
                else if (!mMyTurn)
                    static_cast<States::GameState*>(mGameState)->get_world().activate_enemy_grid(false);

                mGameOver = false;
            }

            if (mReady && mEnemyReady)
            {
                if (!mGameStarted)
                {
                    std::cout << "Im ready and enemy is ready too!";
                    static_cast<States::GameState*>(mGameState)->deactivate_ready_button();
                    mGameStarted = true;
                    mGameOver = false;
                }
                if (!mMsgSent.is_clear())
                {
                    if ((status = mSocket.send(&mMsgSent, sizeof(mMsgSent), sent)) != sf::Socket::Done)
                        decode_status(status);
                    else
                        std::cout << "I sent data to the client!\n";
                    mMsgSent.clear();
                }
            }

            mutex.unlock();
        }
    }
}