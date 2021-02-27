#include "GameState.h"

namespace States
{
	Net::Remote* GameState::mRemote;

	GameState::GameState(StateManager &stateManager, Context context, Net::RemoteType mRemoteType) :
		State(stateManager, context),
		mWorld(context.mWindow),
		mWindow(context.mWindow)
	{
		context.mTextures->load_resource(Textures::ID::READYBUTTON, "assets/readybutton.png");

		sf::Font &font = context.mFonts->get_resource(Fonts::ID::VIKING);
		mButtonReady = new GUI::Button(sf::Vector2f(90.0f, 730.f), context.mTextures->get_resource(Textures::ID::READYBUTTON), "Ready", font, 25);
		mButtonLeave = new GUI::Button(sf::Vector2f(320.0f, 730.f), context.mTextures->get_resource(Textures::ID::READYBUTTON), "Leave", font, 25);

		mButtonReady->set_text_color(sf::Color::White);
		mButtonLeave->set_text_color(sf::Color::White);

		if (mRemoteType == Net::RemoteType::CLIENT)
			static_cast<Net::Client*>(mRemote)->set_game_state(this);
		else
			static_cast<Net::Server*>(mRemote)->set_game_state(this);

		mButtonReady->set_callback([this](void)
		{
			if (mWorld.all_ships_placed())
			{
				mRemote->mReady = true;
			}
		});

		mButtonLeave->set_callback([this](void)
		{
			
		});
	}

	void GameState::render(void)
	{
		mWorld.draw();
		mButtonReady->draw(mWindow);
		mButtonLeave->draw(mWindow);
	}

	bool GameState::update(sf::Time elapsedTime)
	{
		mMousePosition = sf::Mouse::getPosition(*get_context().mWindow);
		mButtonReady->update(mMousePosition);
		mButtonLeave->update(mMousePosition);
		mWorld.update();

		return true;
	}

	bool GameState::handle_event(const sf::Event &event)
	{
		mButtonReady->handle_event(event);
		mButtonLeave->handle_event(event);

		switch (event.type)
		{
			case sf::Event::MouseButtonPressed:
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