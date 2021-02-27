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
		sf::Vector2i mMousePosition;
		bool mGameOver;
		bool mPlayAgain;
		bool mIsWon;
		bool mMyTurn;

	public:
		static Remote* mRemote;

		GameState(StateManager &stateManager, Context context);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}