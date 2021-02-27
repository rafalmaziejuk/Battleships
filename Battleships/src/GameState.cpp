#include "GameState.h"

namespace States
{
	Remote* GameState::mRemote;

	GameState::GameState(StateManager &stateManager, Context context) :
		State(stateManager, context),
		mWorld(context.mWindow)
	{

	}

	void GameState::render(void)
	{
		mWorld.draw();
	}

	bool GameState::update(sf::Time elapsedTime)
	{
		mMousePosition = sf::Mouse::getPosition(*get_context().mWindow);
		mWorld.update();

		return true;
	}

	bool GameState::handle_event(const sf::Event &event)
	{
		switch (event.type)
		{
			case sf::Event::MouseButtonPressed:
				mWorld.handle_input(event.mouseButton, true);
				break;

			case sf::Event::MouseButtonReleased:
				mWorld.handle_input(event.mouseButton, false);
				break;

			default: break;
		}

		return true;
	}
}