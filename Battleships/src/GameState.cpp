#include "GameState.h"

GameState::GameState(sf::RenderWindow *window) :
	State(window),
	mShipsGrid(new Grid(sf::Vector2i(50, 50))),
	mTargetsGrid(new Grid(sf::Vector2i(650, 50)))
{
	mBackgroundTexture.loadFromFile("assets/gamebg.png");
	mBackground.setTexture(mBackgroundTexture);
}

GameState::~GameState(void)
{
	delete mShipsGrid;
	delete mTargetsGrid;
}

void GameState::render(void)
{
	State::get_window()->draw(mBackground);
	mShipsGrid->draw(State::get_window());
	mTargetsGrid->draw(State::get_window());
}

void GameState::update(sf::Time elapsedTime)
{
	mShipsGrid->update_cursor(sf::Mouse::getPosition(*State::get_window()));
	mTargetsGrid->update_cursor(sf::Mouse::getPosition(*State::get_window()));
}

void GameState::handle_event(sf::Event &event)
{
	switch (event.type)
	{
		default: break;
	}
}