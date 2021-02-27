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

		static_cast<GUI::InputBox *>(mWidgets[0])->set_entered_text(mMyIp.toString());
	}

	ConnectState::~ConnectState(void)
	{
		if (!GameState::mRemote->is_connected_with_remote())
			delete GameState::mRemote;

		for (auto &widget : mWidgets)
			delete widget;
	}

	void ConnectState::set_gui(Context context)
	{
		mScreen.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_SCREEN));
		mConnectionStatus.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_STATUS));
		mConnectionStatus.setPosition(sf::Vector2f(238.5f, 355.0f));

		sf::Font& font = context.mFonts->get_resource(Fonts::ID::VIKING);

		mWidgets.push_back(new GUI::InputBox(sf::Vector2f(475.0f, 315.0f), sf::Vector2i(300, 50), font, 25, 14));
		mWidgets.push_back(new GUI::InputBox(sf::Vector2f(475.0f, 412.0f), sf::Vector2i(300, 50), font, 25, 5));
		mWidgets[0]->set_align_mode(GUI::Widget::AlignOptions::LEFT);
		mWidgets[1]->set_align_mode(GUI::Widget::AlignOptions::LEFT);

		mWidgets.push_back(new GUI::Button(sf::Vector2f(523.0f, 480.0f), context.mTextures->get_resource(Textures::ID::CONNECTBUTTON1), "Connect", font, 25));
		mWidgets.push_back(new GUI::Button(sf::Vector2f(360.0f, 560.0f), context.mTextures->get_resource(Textures::ID::BACKBUTTON)));

		static_cast<GUI::Button *>(mWidgets[2])->set_callback([this](void)
		{
			if (mRemoteType == Net::RemoteType::SERVER)
			{
				if (mWidgets[1]->get_text().length() > 0 && !mServer->is_running())
				{
					mServer->set_port(std::stoi(mWidgets[1]->get_text()));
					mServer->start();
					mIsRemoteThreadRunning = true;
				}
			}
			else if (mRemoteType == Net::RemoteType::CLIENT)
			{
				if (mWidgets[1]->get_text().length() > 0 && !mClient->is_running())
				{
					mClient->set_port(std::stoi(mWidgets[1]->get_text()));
					mClient->set_ip(sf::IpAddress(mWidgets[0]->get_text()));
					mClient->start();
					mIsRemoteThreadRunning = true;
				}
			}
		});
		
		static_cast<GUI::Button *>(mWidgets[3])->set_callback([this](void)
		{
			delete_state();
			add_state(ID::MAIN_MENU);
		});
	}

	void ConnectState::render(void)
	{
		sf::RenderWindow *window = get_context().mWindow;

		window->draw(mScreen);

		for (auto &widget : mWidgets)
			widget->draw(window);

		if (mIsRemoteThreadRunning)
			window->draw(mConnectionStatus);
	}

	bool ConnectState::update(sf::Time elapsedTime)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*get_context().mWindow);

		for (auto &widget : mWidgets)
			widget->update(mousePosition);

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
		for (auto &widget : mWidgets)
			widget->handle_event(event);

		return true;
	}
}