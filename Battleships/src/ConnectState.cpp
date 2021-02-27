#include "ConnectState.h"
#include "ResourceManager.h"
#include "InputBox.h"
#include "Button.h"

#include <SFML/Graphics/RenderWindow.hpp>

extern RemoteType mRemoteType;


namespace States
{
	ConnectState::ConnectState(StateManager &stateManager, Context context) :
		State(stateManager, context),
		mScreen()
	{
		mScreen.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_SCREEN));
		set_gui(context);
	}

	ConnectState::~ConnectState(void)
	{
		for (auto &widget : mWidgets)
			delete widget;
	}

	void ConnectState::set_gui(Context context)
	{
		mScreen.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_SCREEN));
		mConnectionStatus.setTexture(context.mTextures->get_resource(Textures::ID::CONNECT_STATUS));
		mConnectionStatus.setPosition(sf::Vector2f(238.5f, 355.0f));

		sf::Font& font = context.mFonts->get_resource(Fonts::ID::VIKING);

		mWidgets.push_back(new GUI::InputBox(sf::Vector2f(475.0f, 315.0f), sf::Vector2i(300, 50), font, 25, 14));
		mWidgets.push_back(new GUI::InputBox(sf::Vector2f(475.0f, 412.0f), sf::Vector2i(300, 50), font, 25, 5));
		mWidgets.push_back(new GUI::Button(sf::Vector2f(523.0f, 480.0f), context.mTextures->get_resource(Textures::ID::CONNECTBUTTON1), "Connect", font, 25));
		mWidgets.push_back(new GUI::Button(sf::Vector2f(360.0f, 560.0f), context.mTextures->get_resource(Textures::ID::BACKBUTTON)));
		
		mWidgets[0]->set_align_mode(GUI::Widget::AlignOptions::LEFT);
		mWidgets[1]->set_align_mode(GUI::Widget::AlignOptions::LEFT);
		
		static_cast<GUI::Button *>(mWidgets[3])->set_callback([this](void)
		{
			delete_state();
			add_state(ID::MAIN_MENU);
		});
	}

	void ConnectState::render(void)
	{
		sf::RenderWindow *window = get_context().mWindow;

		window->draw(mScreen);
		
		for (auto &widget : mWidgets)
			widget->draw(window);
	}

	bool ConnectState::update(sf::Time elapsedTime)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*get_context().mWindow);

		for (auto &widget : mWidgets)
			widget->update(mousePosition);

		return true;
	}

	bool ConnectState::handle_event(const sf::Event &event)
	{
		for (auto &widget : mWidgets)
			widget->handle_event(event);

		return true;
	}
}