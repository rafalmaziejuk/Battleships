#pragma once

#include "Remote.h"

#include <thread>

namespace States
{
	class State;
}

namespace Net
{
    class Client : public Remote
    {
    private:

        std::thread* mClientThread;
        sf::IpAddress mRemoteIp;
        unsigned mPort;

        void run_client(void);

        virtual bool establish_connection(void) override;

    public:
        Client();
        ~Client();

        void set_game_state(States::State* state);
        void set_port(const int port);
        void set_ip(const sf::IpAddress ip);

        virtual void start(void) override;
        virtual void stop(void) override;
    };
}