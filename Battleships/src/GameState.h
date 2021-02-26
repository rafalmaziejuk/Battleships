#pragma once

#include <thread>

#include <SFML/Graphics.hpp>

#include "State.h"
#include "World.h"
#include "Server.h"
#include "Client.h"

namespace States
{
	class GameState : public State
	{
	private:
		World mWorld;
		Client* mClient;
		Server* mServer;
		std::thread mThread;

		sf::Vector2i mMousePosition;

	public:
		GameState(Context context);
		virtual ~GameState(void);

		template <typename T>
		void establish_remote(RemoteType remote, T* remotePointer);
		virtual void render(void) override;
		virtual void update(sf::Time elapsedTime) override;
		virtual void handle_event(const sf::Event &event) override;
	};
}