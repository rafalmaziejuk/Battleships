#include "ConnectState.h"
#include "ResourceManager.h"
#include "MenuState.h"

#include <iostream>

//// TO DO //////
/*
*	For host state : 
*	
*	- Connection status info sprite and text, sth like "Waiting for a client on port xxx ..."
*	- And when it is displayed, there should be a button "disconnect" to join listening thread and let go back to entering port again
*	- Figure out how when mServer and mClient pointers can be deleted, they will be forwarded to GameState so that they cant be just deleted in destructor when chanche_state is called
*	
*
*/

ConnectState::ConnectState(Context context) :
	State(context),
	mScreen(),
	mIP(),
	mPort(),
	mMyIp(sf::IpAddress::getLocalAddress()),
	mServer(nullptr),
	mClient(nullptr)
{
	mScreen.setTexture(get_context().mTextures->get_resource(Textures::ID::CONNECT_SCREEN));

	mButton = new ConnectButton(get_context().mTextures->get_resource(Textures::ID::CONNECTBUTTON1), "Connect", sf::Vector2f(523, 480), get_context().mFonts->get_resource(Fonts::ID::VIKING), 25);
	mBackButton = new ConnectButton(get_context().mTextures->get_resource(Textures::ID::BACKBUTTON), "Back", sf::Vector2f(400, 575), get_context().mFonts->get_resource(Fonts::ID::VIKING), 25);
	mBackButton->set_signature_visiblity(false);

	mButton->set_color(sf::Color::Black);

	sf::Font& font = get_context().mFonts->get_resource(Fonts::ID::VIKING);
	mIP = TextBox(sf::Vector2f(475.0f, 315.0f), sf::Vector2f(300.0f, 50.0f), font, 14);
	mPort = TextBox(sf::Vector2f(475.0f, 412.0f), sf::Vector2f(300.0f, 50.0f), font, 5);
}

ConnectState::~ConnectState(void)
{
	delete mButton;
	delete mBackButton;
}

void ConnectState::set_type(RemoteType remote)
{
	mRemoteType = remote;
	if (remote == RemoteType::CLIENT)
	{
		mClient = new Client();
		//mIP.set_entered_text(mMyIp.toString());

	}
	else if (remote == RemoteType::SERVER)
	{
		mServer = new Server();
		mIP.set_entered_text(mMyIp.toString());
		mButton->setString("Host");
	}

}

void ConnectState::render(void)
{
	get_context().mWindow->draw(mScreen);
	mIP.draw(get_context().mWindow);
	mPort.draw(get_context().mWindow);
	mButton->drawButton(get_context().mWindow);
	mBackButton->drawButton(get_context().mWindow);
	
	//// TO DO /////
	/*
	if (mServer->is_running())
	{
		get_context().mWindow->draw(mConnectionInfo);
		get_context().mWindow->draw(mConnectionInfoSprite);
	}
	*/
}

void ConnectState::update(sf::Time elapsedTime)
{
	mButtonClicked = mButton->update(get_context().mWindow, mIsPressed);
	if(mButtonClicked == ButtonID::NONE)
		mButtonClicked = mBackButton->update(get_context().mWindow, mIsPressed);

	if (mButtonClicked != ButtonID::NONE)
	{
		switch (mButtonClicked)
		{
		case ButtonID::C_HOST:
			if (mPort.get_text().length() > 0 && !mServer->is_running())
			{
				// TU TRZEBA ZROBIC ZEBY NIE KLIKALO 10 RAZY TYLKO RAZ ZEBY SIE 1 WATEK TWORZYL ( ALE JUZ PRAWIE DZIALA )

				mServer->set_port(stoi(mPort.get_text()));
				std::cout << "Waiting for connections... on port " << mPort.get_text()<<"\n";
				mServer->start();
				////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
			//StateManager::get_instance().change_state<GameState>(get_context());
			//static_cast<ConnectState*>(StateManager::get_instance().get_state())->set_type(RemoteType::SERVER);
			break;
		case ButtonID::C_CONNECT:
			//StateManager::get_instance().change_state<ConnectState>(get_context());
			//static_cast<ConnectState*>(StateManager::get_instance().get_state())->set_type(RemoteType::CLIENT);
		case ButtonID::C_BACK: 
			StateManager::get_instance().change_state<MenuState>(get_context());
			break;
		}

	}

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
