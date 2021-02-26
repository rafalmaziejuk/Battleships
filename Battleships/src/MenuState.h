#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "Button.h"
#include "Client.h"
#include "Server.h"

namespace States
{
	class MenuState : public State
	{
	private:
		sf::Sprite mBackground;

	private:
		GUI::Button mHostButton;
		GUI::Button mConnectButton;
		GUI::Button mExitButton;

	public:
		MenuState(Context context);
		virtual ~MenuState(void);

		virtual void render(void) override;
		virtual void update(sf::Time elapsedTime) override;
		virtual void handle_event(const sf::Event &event) override;
	};
}