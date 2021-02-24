#include "GameState.h"

GameState::GameState(Context context) :
	State(context),
	mWorld(context.mWindow)
{
	
}

GameState::~GameState(void)
{
	
}

template <typename T>
void GameState::establish_remote(RemoteType remote, T* remotePointer)
{
	if (remote == RemoteType::CLIENT)
		mClient = remotePointer;
	else if (remote == RemoteType::SERVER)
		mServer = remotePointer;
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
}