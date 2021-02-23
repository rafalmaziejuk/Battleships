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
	sf::Font &font = get_context().mFonts->get_resource(Fonts::ID::VIKING);
	sf::Texture &texture = get_context().mTextures->get_resource(Textures::ID::BUTTON1);

	mIP = TextBox(sf::Vector2f(485.0f, 325.0f), 200.0f, 25, font, 14);
	//mPort = TextBox(sf::Vector2f(50.0f, 50.0f), sf::Vector2f(20.0f, 20.0f), font);
}

ConnectState::~ConnectState(void)
{

}

void ConnectState::render(void)
{
	get_context().mWindow->draw(mScreen);
	mIP.draw(get_context().mWindow);
	//mPort.draw(get_context().mWindow);
}

void ConnectState::update(sf::Time elapsedTime)
{

}

void ConnectState::handle_event(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
		{
			std::cout << event.mouseButton.x << " " << event.mouseButton.y << std::endl;
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
