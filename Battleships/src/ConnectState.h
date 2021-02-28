#pragma once

#include "State.h"
#include "Remote.h"
#include "WidgetContainer.h"

#include <SFML/Graphics/Sprite.hpp>

namespace Net
{
	class Server;
	class Client;
}

namespace GUI
{
	class Widget;
}

namespace States
{
	class ConnectState : public State
	{
	private:
		enum class Widgets : uint8_t
		{
			IB_IP,
			IB_PORT,
			B_CONNECT,
			B_CANCEL,
			B_BACK
		};

	private:
		sf::Sprite mScreen;
		sf::Sprite mConnectionStatus;

	private:
		GUI::WidgetContainer<Widgets> mWidgets;
		void set_gui(Context context);

	private:
		Net::RemoteType mRemoteType;
		sf::IpAddress mMyIp;		// User's IP
		
		Net::Server* mServer;			// Server
		Net::Client* mClient;			// Client
		bool mIsRemoteThreadRunning;

	public:
		ConnectState(StateManager &stateManager, Context context, Net::RemoteType type);
		virtual ~ConnectState(void);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}