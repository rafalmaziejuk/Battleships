#include "Client.h"
#include <iostream>

namespace Net
{
    Client::Client()
        : Remote(), mPort(0), mClientThread(nullptr), mGameState(nullptr)
    {
        //mSocket.setBlocking(true);
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
        Ship* temp = world.is_ship_choosen(coord);
        sf::Socket::Status status;
        size_t sent;

        mMsgSent.clear();
        if (temp == nullptr)
        {
            std::cout << "Enemy missed !\n";
            world.get_player_grid().mShotTiles[coord.x][coord.y] = TileStatus::MISS;
            mMsgSent.ID = PlayerAction::MISS;
        }
        else
        {
            std::cout << "Enemy hit your ship!\n";
            world.get_player_grid().mShotTiles[coord.x][coord.y] = TileStatus::HIT;
            mMsgSent.ID = PlayerAction::HIT;
        }
        if ((status = mSocket.send(&mMsgSent, sizeof(mMsgSent), sent)) != sf::Socket::Done)
            decode_status(status);
        else
        {
            std::cout << "I sent information about missile accuracy to remote!\n";
        }
        mMsgSent.clear();
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
        case PlayerAction::HIT:
            std::cout << "Ship is hit!";
            world.get_enemy_grid().mShotTiles[mRecentlyFiredMissile.x][mRecentlyFiredMissile.y] = TileStatus::HIT;

            std::cout << "\n";
            break;
        case PlayerAction::MISS:
            std::cout << "You missed! :( ";
            world.get_enemy_grid().mShotTiles[mRecentlyFiredMissile.x][mRecentlyFiredMissile.y] = TileStatus::MISS;

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
            mMyTurn = true;
            world.activate_enemy_grid(true);

            break;
        }
        case PlayerAction::DISCONNECT:
            std::cout << "DISCONNECT";
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

        bool enemyKnowsThatImReady = false;
        bool readyButtonDisabled = false;

        while (!mDone)
        {

            // data exhange appears every 0,5 s
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
            }


            if (mReady && !enemyKnowsThatImReady)
            {
                mMsgSent.ID = PlayerAction::READY;
                if ((status = mSocket.send(&mMsgSent, sizeof(mMsgSent), sent)) != sf::Socket::Done)
                    decode_status(status);
                else
                {
                    std::cout << "I sent information about being ready to battle!\n";
                    enemyKnowsThatImReady = true;
                }
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

            mutex.unlock();
        }
    }
}