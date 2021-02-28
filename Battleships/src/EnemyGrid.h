#pragma once

#include "Grid.h"

class EnemyGrid : public Grid
{
private:
	
public:

	unsigned mHitShips;

	EnemyGrid(const sf::Vector2i gridStart);
	~EnemyGrid();

	void draw(sf::RenderWindow* window);
	void update(void);

	void fire_missile(const sf::Vector2i position);
	void draw_dots(sf::RenderWindow* window);

};

