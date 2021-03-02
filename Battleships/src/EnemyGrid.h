#pragma once

#include "Grid.h"

class EnemyGrid : public Grid
{
private:
	
public:

	EnemyGrid(const sf::Vector2i gridStart);
	~EnemyGrid();

	void draw(sf::RenderWindow* window);
	void reset(void);

	void fire_missile(const sf::Vector2i position);
	void draw_dots(sf::RenderWindow* window);
	void update_grid_after_ship_sank(void);
	void update_shot_tiles(Net::PlayerAction action, sf::Vector2i missilePos);

};

