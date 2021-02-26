#include "Client.h"
#include <iostream>

Client::Client()
    : Remote(), mPort(0), mClientThread(nullptr)
{

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

void Client::run_client(void)
{

    // Connect to the server
    if (mSocket.connect(mRemoteIp, mPort) != sf::Socket::Done)
        return;
    //cls(0,40);
    std::cout << "Connected to server " << mRemoteIp << std::endl;
    while (true)
    {


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

    }
}