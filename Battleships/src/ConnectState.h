#pragma once

#include "GameState.h"
#include "Server.h"
#include "Client.h"
#include "State.h"
#include "InputBox.h"
#include "Button.h"




#include <SFML/Graphics/Sprite.hpp>

namespace States
{
	// Connect State used for Host and Client connection establishment 
	class ConnectState : public State
	{
	private:
		sf::Sprite mScreen;			// Screen image
		sf::Sprite mConnectionStatus;

	private:
		GUI::InputBox mIpInputBox;		// IP textbox
		GUI::InputBox mPortInputBox;	// Port textbox
		GUI::Button mButton;			// Host/Connect button
		GUI::Button mBackButton;		// Back to menu button
		GUI::Button mCancelButton;		// Cancel connection button

	private:
		sf::IpAddress mMyIp;		// User's IP
		
		Net::Server* mServer;			// Server
		Net::Client* mClient;			// Client
		bool mIsRemoteThreadRunning;

		void init_GUI(Context context);
		void init_button_callbacks(void);

	public:
		ConnectState(StateManager &stateManager, Context context);
		virtual ~ConnectState(void);

		void set_type(void);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}