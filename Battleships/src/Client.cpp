#include "Client.h"
#include <iostream>
#include "World.h"
#include "Grid.h"
#include "State.h"
#include "GameState.h"

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

        // Trying to connect until connection is established
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
        bool connectionStatus = establish_connection();
        if (!connectionStatus)
            return;

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
    }
}