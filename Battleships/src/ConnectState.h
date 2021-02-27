#pragma once

#include "State.h"
#include "Widget.h"
#include "Server.h"
#include "Client.h"

#include <SFML/Graphics/Sprite.hpp>

namespace States
{
	class ConnectState : public State
	{
	private:
		sf::Sprite mScreen;

	private:
		std::vector<GUI::Widget *> mWidgets;

	private:
		void set_gui(Context context);

	public:
		ConnectState(StateManager &stateManager, Context context);
		virtual ~ConnectState(void);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}