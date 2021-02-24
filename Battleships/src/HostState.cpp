#include "HostState.h"
#include "ResourceManager.h"
#include <iostream>

HostState::HostState(Context context) :
	State(context),
	mScreen(),
	mIP(),
	mPort()
{
	
	mConnectButton = new ConnectButton(get_context().mTextures->get_resource(Textures::ID::CONNECTBUTTON1), "Connect", sf::Vector2f(523, 480), get_context().mFonts->get_resource(Fonts::ID::VIKING), 25);
	mConnectButton->set_color(sf::Color::Black);
	mScreen.setTexture(get_context().mTextures->get_resource(Textures::ID::CONNECT_SCREEN));
	sf::Font& font = get_context().mFonts->get_resource(Fonts::ID::VIKING);
	sf::Texture& texture = get_context().mTextures->get_resource(Textures::ID::MENUBUTTON1);

	mIP = TextBox(sf::Vector2f(485.0f, 325.0f), 200.0f, 25, font, 14);
	//mPort = TextBox(sf::Vector2f(50.0f, 50.0f), sf::Vector2f(20.0f, 20.0f), font);
}

HostState::~HostState(void)
{

}

void HostState::render(void)
{
	get_context().mWindow->draw(mScreen);
	mIP.draw(get_context().mWindow);
	//mPort.draw(get_context().mWindow);
	mConnectButton->drawButton(get_context().mWindow);
}

void HostState::update(sf::Time elapsedTime)
{
	mConnectButton->update(get_context().mWindow, mIsPressed);
}

void HostState::handle_event(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		mIsPressed = true;
		std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
		break;
	}

	case sf::Event::MouseButtonReleased:
	{
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
					mIP.delete_symbol();
					break;
				}


				default:
				{
					if ((event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == '.')
						mIP.enter_symbol(static_cast<char>(event.text.unicode));

					break;
				}
			}
		}


		break;
	}

	default: break;
	}
}
