#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "ResourceManager.h"
#include "ResourceIdentifiers.h"

class Application : private sf::NonCopyable
{
private:
	static const sf::Time TIME_PER_FRAME;

private:
	sf::RenderWindow mWindow;
	TextureManager mTextures;
	FontManager mFonts;

private:
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumberOfFrames;
	void update_statistics(sf::Time elapsedTime);

	void render(void);
	void process_events(void);
	void update(sf::Time elapsedTime);

public:
	Application(void);
	~Application(void);

	void run(void);
};