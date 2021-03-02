#pragma once

#include "State.h"
#include "World.h"
#include "Server.h"
#include "Client.h"

#include "Button.h"
#include "WidgetContainer.h"

#include <SFML/Graphics.hpp>
#include <thread>

namespace States
{
	class GameState : public State
	{
	public:
		static Net::Remote* mRemote;

	private:
		enum class Widgets
		{
			B_READY,
			B_LEAVE
		};

	private:
		sf::RenderWindow* mWindow;
		World mWorld;
		sf::Vector2i mMousePosition;

	private:
		GUI::WidgetContainer<Widgets> mWidgets;
		void set_gui(Context context);

	public:
		GameState(StateManager &stateManager, Context context, Net::RemoteType mRemoteType);
		virtual ~GameState(void);

		World& get_world(void);
		void deactivate_ready_button(void);
		void activate_ready_button(void);
		void update_ready_button_text(std::string text);
		virtual void render(void) override;
		virtual bool update(sf::Time elapsedTime) override;
		virtual bool handle_event(const sf::Event &event) override;
		
	};
}