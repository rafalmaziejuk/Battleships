#pragma once

#include "Remote.h"

#include <thread>

namespace Net
{
    class Client : public Remote
    {
    private:

        std::thread* mClientThread; // client thread
        sf::IpAddress mRemoteIp;    // host ip
        unsigned mPort;             // port

        
        virtual bool establish_connection(void) override;
        void run_client(void);

    public:
        Client();
        ~Client();

        void set_port(const int port);
        void set_ip(const sf::IpAddress ip);

        virtual void start(void) override;
        virtual void stop(void) override;
    };
}