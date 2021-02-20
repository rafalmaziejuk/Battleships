#include "GameState.h"

GameState::GameState(sf::RenderWindow *window) :
	State(window),
	mShipsGrid(new Grid(sf::Vector2i(50, 50))),
	mTargetsGrid(new Grid(sf::Vector2i(650, 50)))
{

}

GameState::~GameState(void)
{
	delete mShipsGrid;
	delete mTargetsGrid;
}

void GameState::render(void)
{
	mShipsGrid->draw(State::get_window());
	mTargetsGrid->draw(State::get_window());
}

void GameState::update(sf::Time elapsedTime)
{
	mShipsGrid->update_cursor(sf::Mouse::getPosition(*State::get_window()));
	mTargetsGrid->update_cursor(sf::Mouse::getPosition(*State::get_window()));
}

void GameState::handle_input(void)
{
	
}