#include <sstream>
#include <iostream>
#include "Application.h"
#include "StateManager.h"
#include "MenuState.h"
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

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.0 / FPS);

Application::Application(void) :
	mWindow(new sf::RenderWindow(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Battleships")),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumberOfFrames(0)
{
	mWindow->setKeyRepeatEnabled(false);
	mWindow->setFramerateLimit(FPS);
	StateManager::get_instance().change_state<MenuState>(mWindow);

	if (mStatisticsFont.loadFromFile("assets/Sansation.ttf") == false)
		exit(EXIT_FAILURE);

	mStatisticsText.setFont(mStatisticsFont);
	mStatisticsText.setPosition(5.0, 5.0);
	mStatisticsText.setCharacterSize(10);
}

Application::~Application(void)
{

}

void Application::render(void)
{
	mWindow->clear();
	mWindow->draw(mStatisticsText);
	StateManager::get_instance().get_state()->render();
	mWindow->display();
}

void Application::process_events(void)
{
	sf::Event event;
	while (mWindow->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow->close();
				break;
		}
	}
}

void Application::update_statistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumberOfFrames++;

	if (mStatisticsUpdateTime >= sf::seconds(1.0))
	{
		mStatisticsText.setString
		(
			"Frames / Second = " + to_string(mStatisticsNumberOfFrames) + "\n"
			//+ "Time / Update = " + to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumberOfFrames)
		);

		mStatisticsUpdateTime -= sf::seconds(1.0);
		mStatisticsNumberOfFrames = 0;
	}
}

void Application::run(void)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow->isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;

			process_events();
			StateManager::get_instance().get_state()->handle_input();
			StateManager::get_instance().get_state()->update(TIME_PER_FRAME);
		}

		update_statistics(elapsedTime);
		render();
	}
}