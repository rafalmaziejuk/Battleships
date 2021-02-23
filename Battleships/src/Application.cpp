#include <sstream>
#include <iostream>
#include "Application.h"
#include "StateManager.h"
#include "MenuState.h"
#include "ResourceManager.h"
#include "Defines.h"

namespace
{
	template <typename T>
	std::string to_string(const T &value)
	{
		std::stringstream stream;
		stream << value;

		return stream.str();
	}
}

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
	mTextures.load_resource(Textures::ID::BUTTON1, "assets/button1.png");
	mTextures.load_resource(Textures::ID::BUTTON2, "assets/button2.png");
	mTextures.load_resource(Textures::ID::BUTTON3, "assets/button3.png");
	mTextures.load_resource(Textures::ID::MENU_BACKGROUND, "assets/menubg.jpg");
	mSounds.load_resource(Sounds::ID::SOUND1, "assets/song.wav");

	State::Context context(mWindow, mTextures, mFonts);
	StateManager::get_instance().change_state<MenuState>(context);

	mStatisticsText.setFont(mFonts.get_resource(Fonts::ID::SANSATION));
	mStatisticsText.setPosition(5.0f, 5.0f);
	mStatisticsText.setCharacterSize(10);
	mStatisticsText.setFillColor(sf::Color::Black);
}

Application::~Application(void)
{

}

void Application::render(void)
{
	mWindow.clear();

	StateManager::get_instance().get_state()->render();
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void Application::process_events(void)
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		StateManager::get_instance().get_state()->handle_event(event);
		
		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Application::update_statistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumberOfFrames++;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS = " + to_string(mStatisticsNumberOfFrames) + "\n");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumberOfFrames = 0;
	}
}

void Application::run(void)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//sf::Sound sound;
	//sound.setBuffer(mSounds.get_resource(Sounds::ID::SOUND1));
	//sound.play();
	//
	//sf::Music music;
	//music.openFromFile("assets/song.wav");
	//music.play();
	//

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			process_events();
			StateManager::get_instance().get_state()->update(TIME_PER_FRAME);
		}

		update_statistics(elapsedTime);
		render();
	}
}