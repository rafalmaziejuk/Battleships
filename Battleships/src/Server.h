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
        States::State* mGameState;

        unsigned mPort;


        void run_server(void);
        void handle_missile(World& world, const sf::Vector2i coord);
        void update_grid(Grid& grid);
        void handle_message(message msg);

        virtual bool establish_connection(void) override;
    public:
        Host();
        ~Host();

        void set_game_state(States::State* state);
        void set_port(const int port);
        virtual void start(void) override;
        virtual void stop(void) override;

    };

}