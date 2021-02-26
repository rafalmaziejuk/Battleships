#pragma once

#include "State.h"
#include "InputBox.h"
#include "Button.h"
#include "Server.h"
#include "Client.h"

#include <SFML/Graphics/Sprite.hpp>

namespace States
{
	// Connect State used for Host and Client connection establishment 
	class ConnectState : public State
	{
	private:
		sf::Sprite mScreen;			// Screen image

	private:
		GUI::InputBox mIpInputBox;				// IP textbox
		GUI::InputBox mPortInputBox;				// Port textbox
		GUI::Button mButton;			// Host/Connect button
		GUI::Button mBackButton;		// Back to menu button

	private:
		sf::IpAddress mMyIp;		// User's IP
		
		Server* mServer;			// Server
		Client* mClient;			// Client

	public:
		ConnectState(StateManager &stateManager, Context context);
		virtual ~ConnectState(void);

		void set_type(void);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}