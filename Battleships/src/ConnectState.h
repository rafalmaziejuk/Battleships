#pragma once

#include "TextBox.h"
#include "State.h"
#include "ConnectUIComponents.h"
#include "Server.h"
#include "Client.h"
#include "Defines.h"

// Connect State used for Host and Client connection establishment 
class ConnectState : public State
{
private:
	sf::Sprite mScreen;			// Screen image

private:	
	sf::IpAddress mMyIp;		// User's IP
	TextBox mIP;				// IP textbox
	TextBox mPort;				// Port textbox
	Button* mButton;			// Host/Connect button
	Button* mBackButton;		// Back to menu button
	ButtonID mButtonClicked;	// ButtonID
	bool mIsPressed = false;	// Is mouse pressed
	RemoteType mRemoteType;		// Remote type c {HOST,CLIENT}
	Server* mServer;			// Server
	Client* mClient;			// Client
	
public:
	// Constructor / Destructor
	ConnectState(Context context);
	virtual ~ConnectState(void);

	// Method
	void set_type(RemoteType remote);
	
	// Virtual methods
	virtual void render(void) override;
	virtual void update(sf::Time elapsedTime) override;
	virtual void handle_event(const sf::Event &event) override;
};