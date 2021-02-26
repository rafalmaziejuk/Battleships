#include "Server.h"

Server::Server()
    : Remote(), mPort(0),mServerThread(nullptr)
{
    mListener.setBlocking(false);
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
        }
        if (mDone)
        {
            mListener.close();
            return false;
        }
    }
    return true;
}

void Server::run_server(void)
{

    if (mListener.listen(mPort) != sf::Socket::Done)
        return;
    
    bool status = establish_connection();
    if (!status)
        return;

    while (!mDone)
    {
        // data exhange appears every 0,5 s
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << ".";
        /*
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
        */
    }
    system("pause");
}