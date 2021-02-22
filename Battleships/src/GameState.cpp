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
	mMousePosition = sf::Mouse::getPosition(*get_context().mWindow);
	mWorld.update();
}

void GameState::handle_event(const sf::Event &event)
{
	mWorld.handle_input(mMousePosition, event);
}