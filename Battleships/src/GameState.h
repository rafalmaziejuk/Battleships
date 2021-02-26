#pragma once

#include "State.h"
#include "World.h"
#include "Server.h"
#include "Client.h"

#include <SFML/Graphics.hpp>

#include <thread>

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
		GameState(StateManager &stateManager, Context context);

		template <typename T>
		void establish_remote(RemoteType remote, T* remotePointer);
		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}