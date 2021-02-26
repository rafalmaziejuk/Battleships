#pragma once

#include "Remote.h"
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
    bool establish_connection(void);
public:
    Server();
    ~Server();


    void set_port(const int port);
    void start(void);
    void stop(void);
};
