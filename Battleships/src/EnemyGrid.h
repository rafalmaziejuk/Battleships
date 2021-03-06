#pragma once

#include "Grid.h"


const int MAX_SHIP_LENGHT = 4; // maxiumum ship lenght

class EnemyGrid : public Grid
{
public:
	/* constructor / destructor */
	EnemyGrid(const sf::Vector2i gridStart);
	~EnemyGrid();

	/* drawing/updating */
	
	void draw(sf::RenderWindow* window);												
	void draw_updated_shot_fields(sf::RenderWindow* window);							// drawing dots in missed fields and red ship sprites in hit fields 
	void reset(void);																	// grid reset

	void set_up_ship_hint(sf::Texture& texture, sf::Texture& texture2, sf::Texture& texture3);

	/* missile handling */

	int update_grid_after_ship_sank(sf::Vector2i missilePos, sf::Vector2i cameFrom);	// updating grid after hit and sinking
	void update_grid_after_hit_part(sf::Vector2i missilePos);							// updating grid after missile hit a part of a ship
	void update_grid_after_hit_one(sf::Vector2i missilePos);							// updating grid after missile hit a one lenght ship
	void update_shot_tiles(Net::MessageCode action, sf::Vector2i missilePos);			// updating after getting a response about missile accuracy
	
	void handle_missile_hit(Net::MessageCode action, sf::Vector2i recentlyFiredMissile);
	void handle_miss(sf::Vector2i recentlyFiredMissile);
};

