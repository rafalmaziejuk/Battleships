#pragma once

#include "Remote.h"
#include "World.h"
#include "Grid.h"

#include <iostream>
#include <thread>
#include <atomic>

class Server : public Remote
{
private:

    sf::TcpListener mListener;
    std::thread* mServerThread;
    unsigned mPort;

    
    void run_server(void);
    void update_game_status(World& world);
    void update_grid(Grid& grid);

    virtual bool establish_connection(void) override;
public:
    Server();
    ~Server();


    void set_port(const int port);
    virtual void start(void) override;
    virtual void stop(void) override;
};
