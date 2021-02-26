#pragma once

#include "InputBox.h"
#include "State.h"
#include "Button.h"
#include "Server.h"
#include "Client.h"

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
		RemoteType mRemoteType;		// Remote type c {HOST,CLIENT}
		Server* mServer;			// Server
		Client* mClient;			// Client

	public:
		ConnectState(Context context);
		virtual ~ConnectState(void);

		void set_type(RemoteType remote);

		virtual void render(void) override;
		virtual void update(sf::Time elapsedTime) override;
		virtual void handle_event(const sf::Event &event) override;
	};
}