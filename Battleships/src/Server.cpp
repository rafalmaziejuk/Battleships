#include "Server.h"

namespace Net
{
    Server::Server()
        : Remote(), mPort(0),mServerThread(nullptr), mGameState(nullptr)
    {
        mListener.setBlocking(false);
        mMyTurn = true;
    }

    Server::~Server()
    {

    }

    void Server::set_game_state(States::State* state)
    {
        mGameState = state;
    }

    void Server::set_port(const int port)
    {
        mPort = port;
    }

    void Server::start(void)
    {
        mIsRunning = true;
        mServerThread = new std::thread(&Server::run_server, this);
    }

    void Server::stop(void)
    {
        mIsRunning = false;
        mDone = true;
        mServerThread->join();
        delete mServerThread;
        mDone = false;
    }

    bool Server::establish_connection(void)
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

    void Server::handle_missile(World& world, const sf::Vector2i coord)
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
        //std::cout << "Enemy hit your ship!\n";
    }

    void Server::update_grid(Grid& grid)
    {
        
    }

    void Server::handle_message(message msg)
    {
        std::cout << "msgID (" << (int)msg.ID << ")\n";
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

    void Server::run_server(void)
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
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
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