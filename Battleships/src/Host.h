#pragma once

#include "Remote.h"
#include "World.h"
#include "Grid.h"

#include "State.h"
#include "GameState.h"
#include <iostream>
#include <thread>
#include <atomic>

namespace Net
{
    class Host : public Remote
    {
    private:

        sf::TcpListener mListener;
        std::thread* mServerThread;

        unsigned mPort;


        void run_server(void);
        

        virtual bool establish_connection(void) override;
    public:
        Host();
        ~Host();

        void set_port(const int port);
        virtual void start(void) override;
        virtual void stop(void) override;

    };

}