#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"

class GameState : public State
{
private:

public:
	GameState(sf::RenderWindow *window);
	virtual ~GameState(void);

	virtual void render(void);
	virtual void update(sf::Time elapsedTime);
	virtual void handle_input(void);
};