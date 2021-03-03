#include "Host.h"

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
        if (mListener.listen(mPort) != sf::Socket::Done)
            return;
    
        bool connectionStatus = establish_connection();
        if (!connectionStatus)
        {
            mListener.close();
            return;
        }
 
        wait_till_game_state_ran();

        mSocket.setBlocking(false);

        while (!mDone)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));

            mutex.lock();

            try_receive();
            try_send();

            mutex.unlock();
        }
        system("pause");
    }

}