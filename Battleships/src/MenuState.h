#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"

class MenuState : public State
{
private:
	

public:
	MenuState(sf::RenderWindow *window);
	virtual ~MenuState(void);

	virtual void render(void);
	virtual void update(sf::Time elapsedTime);
	virtual void handle_input(void);
};