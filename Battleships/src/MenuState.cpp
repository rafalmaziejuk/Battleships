#include <iostream>

#include "MenuState.h"
#include "GameState.h"
#include "ConnectState.h" 
#include "StateManager.h"

MenuState::MenuState(Context context) :
	State(context),
	mBackground()
{
	mBackground.setTexture(get_context().mTextures->get_resource(Textures::ID::MENU_BACKGROUND));
	mBackground.setScale(0.95f, 0.95f);
	mMouseClicked = false;

	sf::Font &font = get_context().mFonts->get_resource(Fonts::ID::VIKING);
	mButtons.push_back(new MenuButton(get_context().mTextures->get_resource(Textures::ID::BUTTON1), "Host", sf::Vector2f(100, 200), font, 25));
	mButtons.push_back(new MenuButton(get_context().mTextures->get_resource(Textures::ID::BUTTON2), "Connect", sf::Vector2f(100, 350), font, 25));
	mButtons.push_back(new MenuButton(get_context().mTextures->get_resource(Textures::ID::BUTTON3), "Exit", sf::Vector2f(100, 500), font, 25));
	mButtonClicked = ButtonID::NONE;
}

MenuState::~MenuState(void)
{
	
}

void MenuState::render(void)
{
	get_context().mWindow->draw(mBackground);
	for (auto& i : mButtons)
		i->drawButton(get_context().mWindow);
}

void MenuState::update(sf::Time elapsedTime)
{
	bool clicked = false;
	 
	for (auto& i : mButtons)
	{
		mButtonClicked = i->update(get_context().mWindow, mMouseClicked);
		if (mButtonClicked != ButtonID::NONE)
		{
			switch (mButtonClicked)
			{
				case ButtonID::M_HOST: clicked = true; StateManager::get_instance().change_state<GameState>(get_context()); break;
				case ButtonID::M_CONNECT:  clicked = true; StateManager::get_instance().change_state<ConnectState>(get_context()); break;
				case ButtonID::M_EXIT: break;
			}

			if (clicked) 
				break;
		}
	}

	mMouseClicked = false;
}

void MenuState::handle_event(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
				mMouseClicked = true;

			break;
		}

		default: break;
	}
}