#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Grid.h"

class GameState : public State
{
private:
	Grid *mShipsGrid;
	Grid *mTargetsGrid;
	sf::Texture mBackgroundTexture;
	sf::Sprite mBackground;

public:
	GameState(sf::RenderWindow *window);
	virtual ~GameState(void);

	virtual void render(void) override;
	virtual void update(sf::Time elapsedTime) override;
	virtual void handle_event(sf::Event &event) override;
};