#include "GameState.h"

States::GameState::GameState(Context context) :
	State(context),
	mWorld(context.mWindow),
	mClient(nullptr),
	mServer(nullptr)
{
	
}

States::GameState::~GameState(void)
{
	
}

template <typename T>
void States::GameState::establish_remote(RemoteType remote, T* remotePointer)
{
	if (remote == RemoteType::CLIENT)
		mClient = remotePointer;
	else if (remote == RemoteType::SERVER)
		mServer = remotePointer;
}

void States::GameState::render(void)
{
	mWorld.draw();
}

void States::GameState::update(sf::Time elapsedTime)
{
	mMousePosition = sf::Mouse::getPosition(*get_context().mWindow);
	mWorld.update();
}

void States::GameState::handle_event(const sf::Event &event)
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