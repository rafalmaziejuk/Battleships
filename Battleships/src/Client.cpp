#include "Client.h"
#include <iostream>

static void decode_status(sf::Socket::Status status)
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

Client::Client()
    : Remote(), mPort(0), mClientThread(nullptr)
{
    mSocket.setBlocking(false);
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
    std::cout << "Trying to connect with " << mRemoteIp << " on port " << mPort << "\n";

    // Connect to the server

    while (!mIsConnectedWithRemote)
    {
        mSocket.connect(mRemoteIp, mPort);
        if (mSocket.getRemotePort()) // when this function returs a valid value it means that conection is established
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
    
    bool status = establish_connection();
    if (!status)
        return;

    while (!mDone)
    {
        // data exhange appears every 0,5 s

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << ".";
        
        
            /*
        int x = -1;
        int y = -1;

        if (mSocket.receive(mPacketSent) != sf::Socket::Done)
            return;


        mPacketReceived >> x >> y;
        std::cout << "Odebralem pakiet " << x << " " << y << "\n";
        //update_grid(mGrid, x, y);


        std::cin >> x >> y;
        mPacketSent << x << y;

        if (mSocket.send(mPacketSent) != sf::Socket::Done)
            return;
        std::cout << "Wyslalem pakiet \n" << x << " " << y << " " << "\n";
        //update_grid(mGrid, x, y);
        mPacketSent.clear();
        */
    }
}