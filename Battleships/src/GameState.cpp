#include "GameState.h"

namespace States
{
	Remote* GameState::mRemote;

	GameState::GameState(StateManager &stateManager, Context context) :
		State(stateManager, context),
		mWorld(context.mWindow),
		mWindow(context.mWindow)
	{
		context.mTextures->load_resource(Textures::ID::READYBUTTON, "assets/readybutton.png");
		mButtonReady = GUI::Button(sf::Vector2f(90.0f, 730.f), context.mTextures->get_resource(Textures::ID::READYBUTTON), "Ready", 25, context.mFonts->get_resource(Fonts::ID::VIKING),sf::Color::White);
		mButtonLeave = GUI::Button(sf::Vector2f(320.0f, 730.f), context.mTextures->get_resource(Textures::ID::READYBUTTON), "Leave", 25, context.mFonts->get_resource(Fonts::ID::VIKING), sf::Color::White);

		if (mRemoteType == RemoteType::CLIENT)
			static_cast<Client*>(mRemote)->set_game_state(this);
		else
			static_cast<Server*>(mRemote)->set_game_state(this);

		mButtonReady.set_callback([this](void)
		{
			if (mWorld.all_ships_placed())
			{
				mRemote->mReady = true;
			}
		});

		mButtonLeave.set_callback([this](void)
		{
			
		});


	}

	void GameState::render(void)
	{
		mWorld.draw();
		mButtonReady.draw(mWindow);
		mButtonLeave.draw(mWindow);
	}

	bool GameState::update(sf::Time elapsedTime)
	{
		mMousePosition = sf::Mouse::getPosition(*get_context().mWindow);
		mButtonReady.update(mMousePosition);
		mButtonLeave.update(mMousePosition);
		mWorld.update();

		return true;
	}

	bool GameState::handle_event(const sf::Event &event)
	{
		switch (event.type)
		{
			case sf::Event::MouseButtonPressed:
				if (mButtonReady.is_mouse_over(mMousePosition))
					mButtonReady.on_click(true);
				else if (mButtonLeave.is_mouse_over(mMousePosition))
					mButtonLeave.on_click(true);

				mWorld.handle_input(event.mouseButton, true, mRemote->mReady);
				break;

			case sf::Event::MouseButtonReleased:
				mWorld.handle_input(event.mouseButton, false, mRemote->mReady);
				break;

			default: break;
		}

		return true;
	}
}