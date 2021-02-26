#include <string>

#include "ConnectState.h"
#include "ResourceManager.h"

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

extern RemoteType mRemoteType;

namespace States
{
	ConnectState::ConnectState(StateManager &stateManager, Context context) :
		State(stateManager, context),
		mScreen(),
		mIpInputBox(),
		mPortInputBox(),
		mMyIp(sf::IpAddress::getLocalAddress()),
		mServer(nullptr),
		mClient(nullptr)
	{
		mScreen.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_SCREEN));
		sf::Font& font = context.mFonts->get_resource(Fonts::ID::VIKING);

		mIpInputBox = GUI::InputBox(sf::Vector2f(475.0f, 315.0f), sf::Vector2i(300, 50), font, 25, 14);
		mPortInputBox = GUI::InputBox(sf::Vector2f(475.0f, 412.0f), sf::Vector2i(300, 50), font, 25, 5);

		mButton = GUI::Button(sf::Vector2f(523.0f, 480.0f), context.mTextures->get_resource(Textures::ID::CONNECTBUTTON1), "Connect", 25, font);
		mBackButton = GUI::Button(sf::Vector2f(360.0f, 560.0f), context.mTextures->get_resource(Textures::ID::BACKBUTTON));

		mButton.set_callback([this](void)
		{
			if (mPortInputBox.get_text().length() > 0 && !mServer->is_running())
			{
				// TU TRZEBA ZROBIC ZEBY NIE KLIKALO 10 RAZY TYLKO RAZ ZEBY SIE 1 WATEK TWORZYL ( ALE JUZ PRAWIE DZIALA )

				mServer->set_port(std::stoi(mPortInputBox.get_text()));
				std::cout << "Waiting for connections... on port " << mPortInputBox.get_text() << "\n";
				mServer->start();
			}
		});

		mBackButton.set_callback([this](void)
		{
			delete_state();
			add_state(ID::MAIN_MENU);
		});

		set_type();
	}

	ConnectState::~ConnectState(void)
	{

	}

	void ConnectState::set_type(void)
	{
		if (mRemoteType == RemoteType::CLIENT)
		{
			mClient = new Client();
			//mIP.set_entered_text(mMyIp.toString());
			std::cout << "Client\n";
		}
		else if (mRemoteType == RemoteType::SERVER)
		{
			mServer = new Server();
			mIpInputBox.set_entered_text(mMyIp.toString());
			//mButton->setString("Host");
			std::cout << "Server\n";
		}
	}

	void ConnectState::render(void)
	{
		sf::RenderWindow *window = get_context().mWindow;

		window->draw(mScreen);
		mIpInputBox.draw(window);
		mPortInputBox.draw(window);
		mButton.draw(window);
		mBackButton.draw(window);

		//// TO DO /////
		/*
		if (mServer->is_running())
		{
			get_context().mWindow->draw(mConnectionInfo);
			get_context().mWindow->draw(mConnectionInfoSprite);
		}
		*/
	}

	bool ConnectState::update(sf::Time elapsedTime)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*get_context().mWindow);

		mButton.update(mousePosition);
		mBackButton.update(mousePosition);

		return true;
	}

	bool ConnectState::handle_event(const sf::Event &event)
	{
		switch (event.type)
		{
			case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

					if (mIpInputBox.is_mouse_over(mousePosition))
						mIpInputBox.on_click(true);
					else
						mIpInputBox.on_click(false);

					if (mPortInputBox.is_mouse_over(mousePosition))
						mPortInputBox.on_click(true);
					else
						mPortInputBox.on_click(false);

					if (mButton.is_mouse_over(mousePosition))
						mButton.on_click(true);

					if (mBackButton.is_mouse_over(mousePosition))
						mBackButton.on_click(true);
				}

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
							if (mIpInputBox.is_focused())
								mIpInputBox.delete_symbol();

							if (mPortInputBox.is_focused())
								mPortInputBox.delete_symbol();

							break;
						}

						default:
						{
							if (mIpInputBox.is_focused())
							{
								if ((event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == '.')
									mIpInputBox.enter_symbol(static_cast<char>(event.text.unicode));
							}

							if (mPortInputBox.is_focused())
							{
								if (event.text.unicode >= '0' && event.text.unicode <= '9')
									mPortInputBox.enter_symbol(static_cast<char>(event.text.unicode));
							}

							break;
						}
					}
				}

				break;
			}

			default: break;
		}

		return true;
	}
}