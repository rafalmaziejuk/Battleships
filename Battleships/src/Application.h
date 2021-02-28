#pragma once

#include "ResourceManager.h"
#include "ResourceIdentifiers.h"
#include "StateManager.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application : private sf::NonCopyable
{
private:
	static const sf::Time TIME_PER_FRAME;

private:
	sf::RenderWindow mWindow;
	TextureManager mTextures;
	FontManager mFonts;
	States::StateManager mStateManager;

private:
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t mStatisticsNumberOfFrames;
	void update_statistics(sf::Time elapsedTime);
	void register_states(void);

	void render(void);
	void process_events(void);
	void update(sf::Time elapsedTime);

public:
	Application(void);

	void run(void);
};