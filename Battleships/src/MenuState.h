#pragma once

#include "State.h"
#include "Button.h"
#include "Client.h"
#include "Server.h"

#include <SFML/Graphics/Sprite.hpp>

namespace States
{
	class MenuState : public State
	{
	private:
		sf::Sprite mBackground;

	private:
		std::vector<GUI::Widget *> mButtons;
		void set_gui(Context context);

	public:
		MenuState(StateManager &stateManager, Context context);
		virtual ~MenuState(void);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}