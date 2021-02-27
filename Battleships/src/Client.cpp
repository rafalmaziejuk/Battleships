#include "Client.h"
#include <iostream>

Client::Client()
    : Remote(), mPort(0), mClientThread(nullptr), mGameState(nullptr)
{
    mSocket.setBlocking(true);
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

    while (!mDone)
    {
        // data exhange appears every 0,5 s


        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << ".";
        
        
            
        int x = -1;
        int y = -1;

        if ((status = mSocket.receive(mPacketReceived)) != sf::Socket::Done)
            decode_status(status);


        mPacketReceived >> x >> y;
        std::cout << "Odebralem pakiet " << x << " " << y << "\n";
        //update_grid(mGrid, x, y);


        std::cin >> x >> y;
        mPacketSent << x << y;

        if ((status = mSocket.send(mPacketSent)) != sf::Socket::Done)
            decode_status(status);
        std::cout << "Wyslalem pakiet \n" << x << " " << y << " " << "\n";
        //update_grid(mGrid, x, y);
        mPacketSent.clear();
        
    }
}