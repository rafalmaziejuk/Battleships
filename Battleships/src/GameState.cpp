#include "GameState.h"

namespace States
{
	Net::Remote* GameState::mRemote;

	GameState::GameState(StateManager &stateManager, Context context, Net::RemoteType mRemoteType) :
		State(stateManager, context),
		mWorld(context.mWindow)
	{
		set_gui(context);

		if (mRemoteType == Net::RemoteType::CLIENT)
			static_cast<Net::Client*>(mRemote)->set_game_state(this);
		else
			static_cast<Net::Host*>(mRemote)->set_game_state(this);

		mWorld.set_remote(mRemote);
	}

	GameState::~GameState(void)
	{
		delete mRemote;
	}

	void GameState::set_gui(Context context)
	{
		context.mTextures->load_resource(Textures::ID::B_READY, "assets/readybutton.png");

		sf::Font &font = context.mFonts->get_resource(Fonts::ID::VIKING);
		sf::Texture &texture = context.mTextures->get_resource(Textures::ID::B_READY);

		mWidgets.insert_widget<GUI::Button>(Widgets::B_READY, new GUI::Button(sf::Vector2f(90.0f, 730.f), texture, "Ready", font, 25));
		mWidgets.insert_widget<GUI::Button>(Widgets::B_LEAVE, new GUI::Button(sf::Vector2f(320.0f, 730.f), texture, "Leave", font, 25));

		mWidgets.get_widget<GUI::Button>(Widgets::B_READY)->set_text_color(sf::Color::White);
		mWidgets.get_widget<GUI::Button>(Widgets::B_LEAVE)->set_text_color(sf::Color::White);

		mWidgets.get_widget<GUI::Button>(Widgets::B_READY)->set_callback([this](void)
		{
			if (mWidgets.get_widget<GUI::Button>(Widgets::B_READY)->get_text() == "Ready")
			{
				if (mWorld.all_ships_placed())
				{
					mRemote->mReady = true;
				}
			}
			else
			{
				mRemote->mReplay = true;
			}
		});

		mWidgets.get_widget<GUI::Button>(Widgets::B_LEAVE)->set_callback([this](void)
		{
			
		});
	}

	World& GameState::get_world(void)
	{
		return this->mWorld;
	}

	void GameState::deactivate_ready_button(void)
	{
		mWidgets.get_widget<GUI::Button>(Widgets::B_READY)->deactivate();
	}

	void GameState::activate_ready_button(void)
	{
		mWidgets.get_widget<GUI::Button>(Widgets::B_READY)->activate();
	}

	void GameState::update_ready_button_text(std::string text)
	{
		mWidgets.get_widget<GUI::Button>(Widgets::B_READY)->set_text(text);
	}

	void GameState::render(void)
	{
		mWorld.draw();
		mWidgets.draw(get_context().mWindow);
	}

	bool GameState::update(sf::Time elapsedTime)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*get_context().mWindow);

		mWidgets.update(mousePosition);
		mWorld.update();

		return true;
	}

	bool GameState::handle_event(const sf::Event &event)
	{
		mWidgets.handle_event(event);
		mWorld.handle_event(event, mRemote->mReady);

		return true;
	}
}