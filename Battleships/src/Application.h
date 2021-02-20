#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Application : private sf::NonCopyable
{
private:
	static const sf::Time TIME_PER_FRAME;

	//sf::Thread mRenderingThread;
	sf::RenderWindow *mWindow;

	void render(void);
	void process_events(void);

private:
	sf::Text mStatisticsText;
	sf::Font mStatisticsFont;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumberOfFrames;
	void update_statistics(sf::Time elapsedTime);

public:
	Application(void);
	~Application(void);

	void run(void);
};