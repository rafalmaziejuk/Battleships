#pragma once

#include "Remote.h"

#include <thread>

class Client : public Remote
{
private:

    std::thread* mClientThread;

    sf::IpAddress mRemoteIp;
    unsigned mPort;

    void run_client(void);
    bool establish_connection(void);

public:
    Client();
    ~Client();

    void set_port(const int port);
    void set_ip(const sf::IpAddress ip);
    void start(void);
    void stop(void);
};
