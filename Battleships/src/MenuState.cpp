#include "MenuState.h"
#include "ResourceManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

RemoteType mRemoteType;

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
		for (auto &button : mButtons)
			delete button;
	}

	void MenuState::set_gui(Context context)
	{
		sf::Font &font = context.mFonts->get_resource(Fonts::ID::VIKING);

		mButtons.push_back(new GUI::Button(sf::Vector2f(100.0f, 200.0f), context.mTextures->get_resource(Textures::ID::MENUBUTTON1), "Host", font, 25));
		mButtons.push_back(new GUI::Button(sf::Vector2f(100.0f, 350.0f), context.mTextures->get_resource(Textures::ID::MENUBUTTON2), "Connect", font, 25));
		mButtons.push_back(new GUI::Button(sf::Vector2f(100.0f, 500.0f), context.mTextures->get_resource(Textures::ID::MENUBUTTON3), "Exit", font, 25));

		for (auto &button : mButtons)
			button->set_text_color(sf::Color::White);

		static_cast<GUI::Button *>(mButtons[0])->set_callback([this](void)
		{
			delete_state();
			add_state(ID::CONNECT_STATE);
			mRemoteType = RemoteType::SERVER;
		});

		static_cast<GUI::Button *>(mButtons[1])->set_callback([this](void)
		{
			delete_state();
			add_state(ID::CONNECT_STATE);
			mRemoteType = RemoteType::CLIENT;
		});

		static_cast<GUI::Button *>(mButtons[2])->set_callback([this](void)
		{
			delete_state();
		});
	}

	void MenuState::render(void)
	{
		sf::RenderWindow *window = get_context().mWindow;

		window->draw(mBackground);

		for (auto &button : mButtons)
			button->draw(window);
	}

	bool MenuState::update(sf::Time elapsedTime)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*get_context().mWindow);

		for (auto &button : mButtons)
			button->update(mousePosition);

		return true;
	}

	bool MenuState::handle_event(const sf::Event &event)
	{
		for (auto &button : mButtons)
			button->handle_event(event);

		return true;
	}
}