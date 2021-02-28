#include "ConnectState.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "Widget.h"
#include "InputBox.h"
#include "Button.h"
#include "Server.h"
#include "Client.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace States
{
	ConnectState::ConnectState(StateManager &stateManager, Context context, Net::RemoteType type) :
		State(stateManager, context),
		mScreen(),
		mConnectionStatus(),
		mMyIp(sf::IpAddress::getLocalAddress()),
		mServer(nullptr),
		mClient(nullptr),
		mRemoteType(type),
		mIsRemoteThreadRunning(false)
	{
		mScreen.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_SCREEN));
		set_gui(context);

		if (mRemoteType == Net::RemoteType::CLIENT)
		{
			GameState::mRemote = new Net::Client();
			mClient = static_cast<Net::Client*>(GameState::mRemote);
		}
		else if (mRemoteType == Net::RemoteType::SERVER)
		{
			GameState::mRemote = new Net::Server();
			mServer = static_cast<Net::Server*>(GameState::mRemote);
		}

		mWidgets.get_widget<GUI::InputBox>(Widgets::IB_IP)->set_entered_text(mMyIp.toString());
	}

	ConnectState::~ConnectState(void)
	{
		if (!GameState::mRemote->is_connected_with_remote())
			delete GameState::mRemote;

		mWidgets.clear_widgets();
	}

	void ConnectState::set_gui(Context context)
	{
		mScreen.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_SCREEN));
		mConnectionStatus.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_STATUS));
		mConnectionStatus.setPosition(sf::Vector2f(238.5f, 355.0f));

		sf::Font& font = context.mFonts->get_resource(Fonts::ID::VIKING);

		mWidgets.insert_widget<GUI::InputBox>(Widgets::IB_IP, new GUI::InputBox(sf::Vector2f(475.0f, 315.0f), sf::Vector2i(300, 50), font, 25, 14));
		mWidgets.insert_widget<GUI::InputBox>(Widgets::IB_PORT, new GUI::InputBox(sf::Vector2f(475.0f, 412.0f), sf::Vector2i(300, 50), font, 25, 5));
		mWidgets.get_widget<GUI::InputBox>(Widgets::IB_IP)->set_align_mode(GUI::Widget::AlignOptions::LEFT);
		mWidgets.get_widget<GUI::InputBox>(Widgets::IB_PORT)->set_align_mode(GUI::Widget::AlignOptions::LEFT);

		mWidgets.insert_widget<GUI::Button>(Widgets::B_CONNECT, new GUI::Button(sf::Vector2f(523.0f, 480.0f), context.mTextures->get_resource(Textures::ID::B_CONNECT), "Connect", font, 25));
		mWidgets.insert_widget<GUI::Button>(Widgets::B_CANCEL, new GUI::Button(sf::Vector2f(523.0f, 470.0f), context.mTextures->get_resource(Textures::ID::B_CANCEL), "Cancel", font, 25));
		mWidgets.insert_widget<GUI::Button>(Widgets::B_BACK, new GUI::Button(sf::Vector2f(360.0f, 560.0f), context.mTextures->get_resource(Textures::ID::B_BACK)));

		mWidgets.get_widget<GUI::Button>(Widgets::B_CONNECT)->deactivate();
		mWidgets.get_widget<GUI::Button>(Widgets::B_CANCEL)->deactivate();

		mWidgets.get_widget<GUI::Button>(Widgets::B_CONNECT)->set_callback([this](void)
		{
			if (mRemoteType == Net::RemoteType::SERVER)
			{
				if (!mServer->is_running())
				{
					mServer->set_port(std::stoi(mWidgets.get_widget(Widgets::IB_PORT)->get_text()));
					mServer->start();
					mIsRemoteThreadRunning = true;
				}
			}
			else if (mRemoteType == Net::RemoteType::CLIENT)
			{
				if (!mClient->is_running())
				{
					mClient->set_ip(sf::IpAddress(mWidgets.get_widget(Widgets::IB_IP)->get_text()));
					mClient->set_port(std::stoi(mWidgets.get_widget(Widgets::IB_PORT)->get_text()));
					mClient->start();
					mIsRemoteThreadRunning = true;
				}
			}

			if (mIsRemoteThreadRunning)
			{
				mWidgets.get_widget<GUI::InputBox>(Widgets::IB_IP)->deactivate();
				mWidgets.get_widget<GUI::InputBox>(Widgets::IB_PORT)->deactivate();
				mWidgets.get_widget<GUI::Button>(Widgets::B_CONNECT)->deactivate();
				mWidgets.get_widget<GUI::Button>(Widgets::B_BACK)->deactivate();
				mWidgets.get_widget<GUI::Button>(Widgets::B_CANCEL)->activate();
			}
		});

		mWidgets.get_widget<GUI::Button>(Widgets::B_CANCEL)->set_callback([this](void)
		{
			if (mRemoteType == Net::RemoteType::SERVER)
			{
				if (mServer->is_running())
				{
					mServer->stop();
					std::cout << "stop";
					mIsRemoteThreadRunning = false;
				}
			}
			else if (mRemoteType == Net::RemoteType::CLIENT)
			{
				if (mClient->is_running())
				{
					mClient->stop();
					std::cout << "stop";
					mIsRemoteThreadRunning = false;
				}
			}

			mWidgets.get_widget<GUI::Button>(Widgets::B_CANCEL)->deactivate();
			mWidgets.get_widget<GUI::InputBox>(Widgets::IB_IP)->activate();
			mWidgets.get_widget<GUI::InputBox>(Widgets::IB_PORT)->activate();
			mWidgets.get_widget<GUI::Button>(Widgets::B_CONNECT)->activate();
			mWidgets.get_widget<GUI::Button>(Widgets::B_BACK)->activate();
		});
		
		mWidgets.get_widget<GUI::Button>(Widgets::B_BACK)->set_callback([this](void)
		{
			delete_state();
			add_state(ID::MAIN_MENU);
		});
	}

	void ConnectState::render(void)
	{
		sf::RenderWindow *window = get_context().mWindow;

		window->draw(mScreen);

		if (mIsRemoteThreadRunning)
			window->draw(mConnectionStatus);

		mWidgets.draw(window);
	}

	bool ConnectState::update(sf::Time elapsedTime)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*get_context().mWindow);

		mWidgets.update(mousePosition);

		if (mWidgets.get_widget(Widgets::IB_IP)->is_active() && mWidgets.get_widget(Widgets::IB_PORT)->is_active())
		{
			if (!mWidgets.get_widget(Widgets::IB_IP)->is_text_empty() && !mWidgets.get_widget(Widgets::IB_PORT)->is_text_empty())
				mWidgets.get_widget<GUI::Button>(Widgets::B_CONNECT)->activate();
			else
				mWidgets.get_widget<GUI::Button>(Widgets::B_CONNECT)->deactivate();
		}

		if (mIsRemoteThreadRunning)
		{
			if (mRemoteType == Net::RemoteType::SERVER && mServer->is_connected_with_remote())
			{
				delete_state();
				add_state(ID::GAME_HOST);
			}
			else if (mRemoteType == Net::RemoteType::CLIENT && mClient->is_connected_with_remote())
			{
				delete_state();
				add_state(ID::GAME_JOIN);
			}
		}

		return true;
	}

	bool ConnectState::handle_event(const sf::Event &event)
	{
		mWidgets.handle_event(event);
		return true;
	}
}