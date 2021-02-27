#include "MenuState.h"
#include "ResourceManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace States
{
	MenuState::MenuState(StateManager &stateManager, Context context) :
		State(stateManager, context),
		mBackground()
	{
		mBackground.setTexture(context.mTextures->get_resource(Textures::ID::MENU_BACKGROUND));
		set_gui(context);
	}

	MenuState::~MenuState(void)
	{
		mWidgets.clear_widgets();
	}

	void MenuState::set_gui(Context context)
	{
		sf::Font &font = context.mFonts->get_resource(Fonts::ID::VIKING);

		mWidgets.insert_widget<GUI::Button>(Widgets::HOST, new GUI::Button(sf::Vector2f(100.0f, 200.0f), context.mTextures->get_resource(Textures::ID::MENUBUTTON1), "Host", font, 25));
		mWidgets.insert_widget<GUI::Button>(Widgets::CONNECT, new GUI::Button(sf::Vector2f(100.0f, 350.0f), context.mTextures->get_resource(Textures::ID::MENUBUTTON2), "Connect", font, 25));
		mWidgets.insert_widget<GUI::Button>(Widgets::EXIT, new GUI::Button(sf::Vector2f(100.0f, 500.0f), context.mTextures->get_resource(Textures::ID::MENUBUTTON3), "Exit", font, 25));

		mWidgets.get_widget<GUI::Button>(Widgets::HOST)->set_text_color(sf::Color::White);
		mWidgets.get_widget<GUI::Button>(Widgets::CONNECT)->set_text_color(sf::Color::White);
		mWidgets.get_widget<GUI::Button>(Widgets::EXIT)->set_text_color(sf::Color::White);

		mWidgets.get_widget<GUI::Button>(Widgets::HOST)->set_callback([this](void)
		{
			delete_state();
			add_state(ID::CONNECT_HOST);
		});

		mWidgets.get_widget<GUI::Button>(Widgets::CONNECT)->set_callback([this](void)
		{
			delete_state();
			add_state(ID::CONNECT_JOIN);
		});

		mWidgets.get_widget<GUI::Button>(Widgets::EXIT)->set_callback([this](void)
		{
			delete_state();
		});
	}

	void MenuState::render(void)
	{
		sf::RenderWindow *window = get_context().mWindow;

		window->draw(mBackground);
		mWidgets.draw(window);
	}

	bool MenuState::update(sf::Time elapsedTime)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*get_context().mWindow);

		mWidgets.update(mousePosition);

		return true;
	}

	bool MenuState::handle_event(const sf::Event &event)
	{
		mWidgets.handle_event(event);

		return true;
	}
}