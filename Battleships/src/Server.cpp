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

void Server::update_grid(Grid& grid)
{

}

void Server::update_game_status(World& world)
{

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

    while (!mDone)
    {
        // data exhange appears every 0,5 s
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << ".";

        
        int x;
        int y;
        std::cin >> x >> y;
        mPacketSent << x << y;

        if ((status = mSocket.send(mPacketSent)) != sf::Socket::Done)
            decode_status(status);
        std::cout << "Wyslalem pakiet " << x << " " << y << " " << "\n";
        //update_grid(mGrid, x, y);
        mPacketSent.clear();
        //x = -1; y = -1;

        if ((status = mSocket.receive(mPacketReceived)) != sf::Socket::Done)
            decode_status(status);

        mPacketReceived >> x >> y;
        std::cout << "Odebralem pakiet " << x << " " << y;

        //update_grid(mGrid, x, y);
        
    }
    system("pause");
}