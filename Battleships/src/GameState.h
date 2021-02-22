#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "World.h"

class GameState : public State
{
private:
	World mWorld;
	sf::Vector2i mMousePosition;

public:
	GameState(Context context);
	virtual ~GameState(void);

	virtual void render(void) override;
	virtual void update(sf::Time elapsedTime) override;
	virtual void handle_event(const sf::Event &event) override;
};