#pragma once

#include "State.h"
#include "Remote.h"

#include <SFML/Graphics/Sprite.hpp>

class Server;
class Client;

namespace GUI
{
	class Widget;
}

namespace States
{
	class ConnectState : public State
	{
	private:
		sf::Sprite mScreen;
		sf::Sprite mConnectionStatus;

	private:
		std::vector<GUI::Widget *> mWidgets;

	private:
		sf::IpAddress mMyIp;
		Server* mServer;
		Client* mClient;
		RemoteType mRemoteType;
		bool mIsRemoteThreadRunning;

	private:
		void set_gui(Context context);

	public:
		ConnectState(StateManager &stateManager, Context context, RemoteType type);
		virtual ~ConnectState(void);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}