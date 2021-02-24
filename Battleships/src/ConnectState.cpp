#include "ConnectState.h"
#include "ResourceManager.h"
#include <iostream>

ConnectState::ConnectState(Context context) :
	State(context),
	mScreen(),
	mIP(),
	mPort()
{
	mScreen.setTexture(get_context().mTextures->get_resource(Textures::ID::CONNECT_SCREEN));
	
	mConnectButton = new ConnectButton(get_context().mTextures->get_resource(Textures::ID::CONNECTBUTTON1), "Connect", sf::Vector2f(523, 480), get_context().mFonts->get_resource(Fonts::ID::VIKING), 25);
	mConnectButton->set_color(sf::Color::Black);

	sf::Font &font = get_context().mFonts->get_resource(Fonts::ID::VIKING);
	mIP = TextBox(sf::Vector2f(475.0f, 315.0f), sf::Vector2f(300.0f, 50.0f), font, 14);
	mPort = TextBox(sf::Vector2f(475.0f, 412.0f), sf::Vector2f(300.0f, 50.0f), font, 5);
}

ConnectState::~ConnectState(void)
{

}

void ConnectState::render(void)
{
	get_context().mWindow->draw(mScreen);
	mIP.draw(get_context().mWindow);
	mPort.draw(get_context().mWindow);
	mConnectButton->drawButton(get_context().mWindow);
}

void ConnectState::update(sf::Time elapsedTime)
{
	mConnectButton->update(get_context().mWindow, mIsPressed);
}

void ConnectState::handle_event(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			mIsPressed = true;
			break;
		}
		
		case sf::Event::MouseButtonReleased:
		{
			mIP.on_click(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			mPort.on_click(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			mIsPressed = false;

			break;
		}

		case sf::Event::TextEntered:
		{
			if (event.text.unicode < 128)
			{
				switch (event.text.unicode)
				{
					case 8:
					{
						if (mIP.is_focused() == true)
							mIP.delete_symbol();

						if (mPort.is_focused() == true)
							mPort.delete_symbol();

						break;
					}

					default:
					{
						if (mIP.is_focused() == true)
						{
							if ((event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == '.')
								mIP.enter_symbol(static_cast<char>(event.text.unicode));
						}
						
						if (mPort.is_focused() == true)
						{
							if (event.text.unicode >= '0' && event.text.unicode <= '9')
								mPort.enter_symbol(static_cast<char>(event.text.unicode));
						}

						break;
					}	
				}
			}
				
			break;
		}

		default: break;
	}
}
