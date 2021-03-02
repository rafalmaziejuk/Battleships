#pragma once

#include "Grid.h"

const int MAX_SHIP_LENGHT = 4;

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
	void update_grid_after_ship_sank(sf::Vector2i missilePos, sf::Vector2i cameFrom);
	void update_shot_tiles(Net::PlayerAction action, sf::Vector2i missilePos);

};

