#pragma once

#include "State.h"
#include "World.h"
#include "Server.h"
#include "Client.h"

#include "Button.h"
#include "ResourceManager.h"

#include <SFML/Graphics.hpp>
#include <thread>

namespace States
{
	class GameState : public State
	{
	private:
		sf::RenderWindow* mWindow;
		World mWorld;
		sf::Vector2i mMousePosition;

		GUI::Button mButtonReady;
		GUI::Button mButtonLeave;
	public:
		static Net::Remote* mRemote;

		GameState(StateManager &stateManager, Context context);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}