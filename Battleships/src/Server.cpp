#include "Server.h"

namespace Net
{
    Server::Server()
        : Remote(), mPort(0),mServerThread(nullptr), mGameState(nullptr)
    {
        mListener.setBlocking(false);
    }

    Server::~Server()
    {

    }

    void Server::set_game_state(States::State* state)
    {
        mGameState = state;
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

    void Server::update_game_status(World& world)
    {

    }

    void Server::update_grid(Grid& grid)
    {

    }

    void Server::handle_message(message msg)
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

        // after this loop GameState pointer is set up correctly so that class attributes can be used
        while(mGameState == nullptr) {}

        mSocket.setBlocking(false);

        int i = 0;

        while (!mDone)
        {
            // data exhange appears every 0,5 s
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << ".";

            if (i %3 == 0)
            {
                mPacketSent << 3 << 5;
                if ((status = mSocket.send(mPacketSent)) != sf::Socket::Done)
                    decode_status(status);
                std::cout << "Wyslalem pakiet " << 3 << " " << 5 << " " << "\n";
                mPacketSent.clear();
            }
            i++;
            /*
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
            */
        }
        system("pause");
    }

}