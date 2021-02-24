#pragma once

#include "TextBox.h"
#include "State.h"
#include "ConnectUIComponents.h"

class ConnectState : public State
{
private:
	sf::Sprite mScreen;

private:
	TextBox mIP;
	TextBox mPort;
	Button* mConnectButton;
	bool mIsPressed = false;

public:
	ConnectState(Context context);
	virtual ~ConnectState(void);

	virtual void render(void) override;
	virtual void update(sf::Time elapsedTime) override;
	virtual void handle_event(const sf::Event &event) override;
};