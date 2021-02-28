#pragma once

#include "State.h"
#include "Button.h"
#include "Client.h"
#include "Server.h"

#include <SFML/Graphics/Sprite.hpp>

#include "WidgetContainer.h"

namespace States
{
	class MenuState : public State
	{
	private:
		enum class Widgets : uint8_t
		{
			B_HOST,
			B_CONNECT,
			B_EXIT
		};

	private:
		sf::Sprite mBackground;

	private:
		GUI::WidgetContainer<Widgets> mWidgets;
		void set_gui(Context context);

	public:
		MenuState(StateManager &stateManager, Context context);
		virtual ~MenuState(void);

		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
	};
}