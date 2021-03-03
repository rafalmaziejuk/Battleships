#include "Client.h"
#include <iostream>

namespace Net
{
    Client::Client()
        : Remote(), mPort(0), mClientThread(nullptr)
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