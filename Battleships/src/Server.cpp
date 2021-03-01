#include "Server.h"

namespace Net
{
    Host::Host()
        : Remote(), mPort(0),mServerThread(nullptr), mGameState(nullptr)
    {
        mListener.setBlocking(false);
        mMyTurn = true;
    }

    Host::~Host()
    {

    }

    void Host::set_game_state(States::State* state)
    {
        mGameState = state;
    }

    void Host::set_port(const int port)
    {
        mPort = port;
    }

    void Host::start(void)
    {
        mIsRunning = true;
        mServerThread = new std::thread(&Host::run_server, this);
    }

    void Host::stop(void)
    {
        mIsRunning = false;
        mDone = true;
        mServerThread->join();
        delete mServerThread;
        mDone = false;
    }

    bool Host::establish_connection(void)
    {
        std::cout << "Server is listening to port " << mPort << ", waiting for connections... \n" << std::endl;

        while (!mIsConnectedWithRemote)
        {
            sf::Socket::Status status = mListener.accept(mSocket);
            if (status == sf::Socket::Done)
            {
                mIsConnectedWithRemote = true;
                std::cout << "Client connected with IP - " << mSocket.getRemoteAddress() << "\n";
            }
            if (mDone)
            {
                mListener.close();
                return false;
            }
        }
        return true;
    }

    void Host::handle_missile(World& world, const sf::Vector2i coord)
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
            // the above should be changed to ///////

            mMsgSent.ID = world.get_player_grid().update_shot_tiles(ship, coord);
            // and returned ID should be handled properly in remote's handle_message()
            /////////////////////////////////////////

            mMyTurn = false;
            world.activate_enemy_grid(false);
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

    void Host::update_grid(Grid& grid)
    {
        
    }

    void Host::handle_message(message msg)
    {
        std::cout << "msgID (" << (int)msg.ID << ")\n";
        World& world = static_cast<States::GameState*>(mGameState)->get_world();

        switch (msg.ID)
        {
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
            
            mMyTurn = false;
            world.activate_enemy_grid(false);

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
            break;
        }
        case PlayerAction::DISCONNECT:
            std::cout << "DISCONNECT";
            break;
        }
    }

    void Host::run_server(void)
    {
        sf::Socket::Status status;

        if (mListener.listen(mPort) != sf::Socket::Done)
            return;
    
        bool connectionStatus = establish_connection();
        if (!connectionStatus)
        {
            mListener.close();
            return;
        }
        mListener.setBlocking(true);

        // after this loop GameState pointer is set up correctly so that class attributes can be used
        while(mGameState == nullptr) {}

        mSocket.setBlocking(false);

        int i = 0;
        size_t received;
        size_t sent;
        bool enemyKnowsThatImReady = false;

        while (!mDone)
        {
            // data exhange appears every 0,05 s
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            //std::cout << ".";

            mutex.lock();
            // Critical section

            if ((status = mSocket.receive(&mMsgReceived,sizeof(message),received)) != sf::Socket::Done){}
                //decode_status(status);
            else if (status == sf::Socket::Done)
            {
                std::cout << "Data received! \n";
                handle_message(mMsgReceived);
            }
            else if (status == sf::Socket::Disconnected)
            {
                // disconnected
                // end server 
                // end state 
                // back to main menu
            }

            if (mReady && !enemyKnowsThatImReady)
            {
                mMsgSent.ID = PlayerAction::READY;
                if ((status = mSocket.send(&mMsgSent,sizeof(mMsgSent),sent)) != sf::Socket::Done)
                    decode_status(status);
                else
                {
                    std::cout << "I sent information about being ready to battle!\n";
                    enemyKnowsThatImReady = true;
                }
                mMsgSent.clear();
            }
            
            if (mReady && mEnemyReady)
            {
                if (!mGameStarted)
                {
                    std::cout << "Im ready and enemy is ready too!";
                    static_cast<States::GameState*>(mGameState)->deactivate_ready_button();
                    mGameStarted = true;
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
            //update_game_status(static_cast<States::GameState*>(mGameState)->get_world());
            
            mutex.unlock();
        }
        system("pause");
    }

}