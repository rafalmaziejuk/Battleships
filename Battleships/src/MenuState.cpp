#include <iostream>
#include "MenuState.h"
#include "GameState.h"
#include "StateManager.h"

MenuState::MenuState(sf::RenderWindow *window) :
	State(window)
{
	init_ui();
}

MenuState::~MenuState(void)
{
	
}

void MenuState::init_ui(void)
{
	mButtonTextures.push_back(new sf::Texture);
	mButtonTextures.back()->loadFromFile("assets/button1.png");
	mButtonTextures.push_back(new sf::Texture);
	mButtonTextures.back()->loadFromFile("assets/button2.png");
	mButtonTextures.push_back(new sf::Texture);
	mButtonTextures.back()->loadFromFile("assets/button3.png");

	mBacgroundTexture.loadFromFile("assets/menubg.jpg");
	mBackground.setTexture(mBacgroundTexture);
	mBackground.setScale(0.95, 0.95);
	mMouseClicked = false;

	mButtons.push_back(new MenuButton(mButtonTextures[0], "Host", sf::Vector2f(100, 200), 25));
	mButtons.push_back(new MenuButton(mButtonTextures[1], "Connect", sf::Vector2f(100, 350), 25));
	mButtons.push_back(new MenuButton(mButtonTextures[2], "Exit", sf::Vector2f(100, 500), 25));
}

void MenuState::render(void)
{
	get_window()->draw(mBackground);
	for (auto& i : mButtons)
		i->drawButton(get_window());
}

void MenuState::update(sf::Time elapsedTime)
{
	mMouseClicked = false;
	for (auto& i : mButtons)
		i->update(get_window(),mMouseClicked);
}

void MenuState::handle_event(sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				StateManager::get_instance().change_state<GameState>(State::get_window());
				mMouseClicked = true;
			}

			break;
		}

		default: break;
	}
}