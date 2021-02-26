#include "Server.h"

Server::Server()
    : Remote(), mPort(0),mServerThread(nullptr)
{

}

Server::~Server()
{

}

void Server::set_port(const int port)
{
    mPort = port;
}

void Server::start(void)
{
    mServerThread = new std::thread(&Server::run_server, this);
    mIsRunning = true;
}

void Server::run_server(void)
{
    if (mListener.listen(mPort) != sf::Socket::Done)
        return;
    std::cout << "Server is listening to port " << mPort << ", waiting for connections... " << std::endl;

    if (mListener.accept(mSocket) != sf::Socket::Done)
        return;
    std::cout << "Client connected: " << mSocket.getRemoteAddress() << std::endl;

    while (true)
    {

        int x;
        int y;
        std::cin >> x >> y;
        mPacketSent << x << y;

        if (mSocket.send(mPacketSent) != sf::Socket::Done)
            return;
        std::cout << "Wyslalem pakiet " << x << " " << y << " " << "\n";
        //update_grid(mGrid, x, y);
        mPacketSent.clear();
        //x = -1; y = -1;

        if (mSocket.receive(mPacketReceived) != sf::Socket::Done)
            return;

        mPacketReceived >> x >> y;
        std::cout << "Odebralem pakiet " << x << " " << y;

        //update_grid(mGrid, x, y);

    }
    system("pause");
}