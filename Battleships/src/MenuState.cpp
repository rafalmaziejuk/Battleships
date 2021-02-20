#include <iostream>
#include "MenuState.h"
#include "GameState.h"
#include "StateManager.h"

MenuState::MenuState(sf::RenderWindow *window) :
	State(window)
{
	
}

MenuState::~MenuState(void)
{
	
}

void MenuState::render(void)
{
	
}

void MenuState::update(sf::Time elapsedTime)
{

}

void MenuState::handle_input(void)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		StateManager::get_instance().change_state<GameState>(State::get_window());
}