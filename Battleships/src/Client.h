#pragma once


#include "Remote.h"
#include "World.h"
#include "Grid.h"
#include "State.h"
#include "GameState.h"

#include <thread>

namespace Net
{
    class Client : public Remote
    {
    private:

        std::thread* mClientThread;
        sf::IpAddress mRemoteIp;
        unsigned mPort;
        States::State* mGameState;

        void run_client(void);
        void update_game_status(World& world);
        void update_grid(Grid& grid);
        void handle_message(message msg);

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