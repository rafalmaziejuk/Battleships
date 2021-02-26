#include "Application.h"
#include "Utility.h"
#include "StateManager.h"
#include "MenuState.h"
#include "ResourceManager.h"
#include "Defines.h"

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0f / FPS);

Application::Application(void) :
	mWindow(sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Battleships", sf::Style::Titlebar | sf::Style::Close)),
	mTextures(),
	mFonts(),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumberOfFrames(0)
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setFramerateLimit(unsigned int(FPS));

	mFonts.load_resource(Fonts::ID::SANSATION, "assets/Sansation.ttf");
	mFonts.load_resource(Fonts::ID::VIKING, "assets/VIKING-FONT.ttf");
	mTextures.load_resource(Textures::ID::MENUBUTTON1, "assets/button1.png");
	mTextures.load_resource(Textures::ID::MENUBUTTON2, "assets/button2.png");
	mTextures.load_resource(Textures::ID::MENUBUTTON3, "assets/button3.png");
	mTextures.load_resource(Textures::ID::MENU_BACKGROUND, "assets/menubg.jpg");
	mTextures.load_resource(Textures::ID::CONNECT_SCREEN, "assets/connectstate.png");
	mTextures.load_resource(Textures::ID::CONNECTBUTTON1, "assets/connectbutton1.png");
	mTextures.load_resource(Textures::ID::BACKBUTTON, "assets/backbutton.png");

	mStatisticsText.setFont(mFonts.get_resource(Fonts::ID::SANSATION));
	mStatisticsText.setPosition(5.0f, 5.0f);
	mStatisticsText.setCharacterSize(10);
	mStatisticsText.setFillColor(sf::Color::Black);

	States::State::Context context(mWindow, mTextures, mFonts);
	States::StateManager::get_instance().change_state<States::MenuState>(context);
}

Application::~Application(void)
{
	
}

void Application::render(void)
{
	mWindow.clear();

	if (!States::StateManager::get_instance().is_empty())
		States::StateManager::get_instance().get_state()->render();

	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::process_events(void)
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (!States::StateManager::get_instance().is_empty())
			States::StateManager::get_instance().get_state()->handle_event(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time elapsedTime)
{
	if (!States::StateManager::get_instance().is_empty())
		States::StateManager::get_instance().get_state()->update(elapsedTime);
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

			if (States::StateManager::get_instance().is_empty())
				mWindow.close();			
		}

		update_statistics(elapsedTime);
		render();
	}
}