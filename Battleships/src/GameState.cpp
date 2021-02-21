#include "GameState.h"

GameState::GameState(Context context) :
	State(context),
	mWorld(context.mWindow)
{
	
}

GameState::~GameState(void)
{
	
}

void GameState::render(void)
{
	mWorld.draw();
}

void GameState::update(sf::Time elapsedTime)
{
	mWorld.update();
}

void GameState::handle_event(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			mWorld.handle_input(sf::Mouse::getPosition(*get_context().mWindow), true);
			break;
		}
		
		case sf::Event::MouseButtonReleased:
		{
			mWorld.handle_input(sf::Mouse::getPosition(*get_context().mWindow), false);
			break;
		}

		default: break;
	}
}