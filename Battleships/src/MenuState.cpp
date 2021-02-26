#include <iostream>

#include "MenuState.h"
#include "GameState.h"
#include "ConnectState.h" 
#include "StateManager.h"

States::MenuState::MenuState(Context context) :
	State(context),
	mBackground()
{
	mBackground.setTexture(get_context().mTextures->get_resource(Textures::ID::MENU_BACKGROUND));

	sf::Font &font = get_context().mFonts->get_resource(Fonts::ID::VIKING);

	mHostButton = GUI::Button(sf::Vector2f(100.0f, 200.0f), get_context().mTextures->get_resource(Textures::ID::MENUBUTTON1), "Host", 25, font);
	mConnectButton = GUI::Button(sf::Vector2f(100.0f, 350.0f), get_context().mTextures->get_resource(Textures::ID::MENUBUTTON2), "Connect", 25, font);
	mExitButton = GUI::Button(sf::Vector2f(100.0f, 500.0f), get_context().mTextures->get_resource(Textures::ID::MENUBUTTON3), "Exit", 25, font);

	mHostButton.set_callback([this](void) 
	{ 
		StateManager::get_instance().change_state<ConnectState>(get_context());
		static_cast<ConnectState *>(StateManager::get_instance().get_state())->set_type(RemoteType::SERVER);
	});

	mConnectButton.set_callback([this](void)
	{
		StateManager::get_instance().change_state<ConnectState>(get_context());
		static_cast<ConnectState *>(StateManager::get_instance().get_state())->set_type(RemoteType::CLIENT);
	});

	mExitButton.set_callback([this](void)
	{
		StateManager::get_instance().delete_state();
	});
}

States::MenuState::~MenuState(void)
{
	
}

void States::MenuState::render(void)
{
	sf::RenderWindow *window = get_context().mWindow;

	window->draw(mBackground);
	mHostButton.draw(window);
	mConnectButton.draw(window);
	mExitButton.draw(window);
}

void States::MenuState::update(sf::Time elapsedTime)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*get_context().mWindow);

	mHostButton.update(mousePosition);
	mConnectButton.update(mousePosition);
	mExitButton.update(mousePosition);
}

void States::MenuState::handle_event(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonReleased:
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);
				
				if (mHostButton.is_mouse_over(mousePosition))
					mHostButton.on_click(true);

				if (mConnectButton.is_mouse_over(mousePosition))
					mConnectButton.on_click(true);

				if (mExitButton.is_mouse_over(mousePosition))
					mExitButton.on_click(true);
			}

			break;
		}

		default: break;
	}
}