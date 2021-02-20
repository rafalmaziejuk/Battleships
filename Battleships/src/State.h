#pragma once

#include <SFML/Graphics.hpp>

class State
{
private:
	sf::RenderWindow *mWindow;

protected:
	sf::RenderWindow * get_window(void) { return mWindow; }

public:
	State(sf::RenderWindow *window = nullptr) : mWindow(window) { }
	virtual ~State(void) { };

	virtual void render(void) = 0;
	virtual void update(sf::Time elapsedTime) = 0;
	virtual void handle_event(sf::Event &event) = 0;
};