#include "Application.h"
#include "Utility.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "MenuState.h"
#include "ConnectState.h"
#include "GameState.h"
#include "Remote.h"

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / 60.0f);

Application::Application(void) :
	mWindow(sf::RenderWindow(sf::VideoMode(1250, 850), "Battleships", sf::Style::Titlebar | sf::Style::Close)),
	mTextures(),
	mFonts(),
	mStateManager(States::State::Context(mWindow, mTextures, mFonts)),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumberOfFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setFramerateLimit(60);

	mFonts.load_resource(Fonts::ID::SANSATION, "assets/Sansation.ttf");
	mFonts.load_resource(Fonts::ID::VIKING, "assets/VIKING-FONT.ttf");
	mTextures.load_resource(Textures::ID::B_MENU1, "assets/button1.png");
	mTextures.load_resource(Textures::ID::B_MENU2, "assets/button2.png");
	mTextures.load_resource(Textures::ID::B_MENU3, "assets/button3.png");
	mTextures.load_resource(Textures::ID::B_CONNECT, "assets/connectbutton1.png");
	mTextures.load_resource(Textures::ID::B_BACK, "assets/backbutton.png");
	mTextures.load_resource(Textures::ID::B_CANCEL, "assets/cancelbutton.png");
	mTextures.load_resource(Textures::ID::BG_MENU, "assets/menubg.jpg");
	mTextures.load_resource(Textures::ID::CONNECT_SCREEN, "assets/connectstate.png");
	mTextures.load_resource(Textures::ID::CONNECT_STATUS, "assets/connectstatus.png");
	
	mStatisticsText.setFont(mFonts.get_resource(Fonts::ID::SANSATION));
	mStatisticsText.setPosition(5.0f, 5.0f);
	mStatisticsText.setCharacterSize(10);
	mStatisticsText.setFillColor(sf::Color::Black);

	register_states();
	mStateManager.add_state(States::ID::MAIN_MENU);
}

void Application::render(void)
{
	mWindow.clear();

	mStateManager.render();
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::process_events(void)
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateManager.handle_event(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time elapsedTime)
{
	mStateManager.update(elapsedTime);
}

void Application::update_statistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumberOfFrames++;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS = " + Utility::to_string(mStatisticsNumberOfFrames) + "\n");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumberOfFrames = 0;
	}
}

void Application::register_states(void)
{
	mStateManager.register_state<States::MenuState>(States::ID::MAIN_MENU);
	mStateManager.register_state<States::ConnectState>(States::ID::CONNECT_HOST, Net::RemoteType::SERVER);
	mStateManager.register_state<States::ConnectState>(States::ID::CONNECT_JOIN, Net::RemoteType::CLIENT);
	mStateManager.register_state<States::GameState>(States::ID::GAME_HOST, Net::RemoteType::SERVER);
	mStateManager.register_state<States::GameState>(States::ID::GAME_JOIN, Net::RemoteType::CLIENT);
}

void Application::run(void)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			process_events();
			update(TIME_PER_FRAME);

			if (mStateManager.is_empty())
				mWindow.close();
		}

		update_statistics(elapsedTime);
		render();
	}
}