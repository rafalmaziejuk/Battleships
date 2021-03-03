#include "Server.h"

namespace Net
{
    Host::Host()
        : Remote(), mPort(0),mServerThread(nullptr)
    {
        mListener.setBlocking(false);
        mMyTurn = true;
        mIStartedGame = true;
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
                if (mMyTurn)
                    static_cast<States::GameState*>(mGameState)->get_world().activate_enemy_grid(true);
                else if(!mMyTurn)
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
            //update_game_status(static_cast<States::GameState*>(mGameState)->get_world());
            
            mutex.unlock();
        }
        system("pause");
    }

}