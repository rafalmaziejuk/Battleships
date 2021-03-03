#pragma once

#include "Grid.h"



class PlayerGrid : public Grid
{
private:

	/* utility functions */

	void add_ship_to_grid(Ship& ship);									// adds ship to the player grid, updates essential components
	void delete_ship_from_grid(Ship& ship);								// deletes ship from the grid
	void update_ship_hint(const int shipId, HintAction action);			// updates ship hint below the grid
	void set_new_ship_segment(sf::Vector2i position, Ship& ship);		// increments ship lenght by adding one tile
	void update_fields(sf::Vector2i position, bool somethingAdded);		// updates field tables around the given tile position 
	

public:
	unsigned mPlacedShips; // ships already placed by user on the grid

	/* constructor / destructor */

	PlayerGrid(sf::Vector2i gridStart);
	~PlayerGrid();

	/* drawing / updating */		
	void draw(sf::RenderWindow* window);			
	void update(Ship& ship, ShipAction action);
	void reset(void);																// grid reset

	/* utility functions */

	bool is_field_free(sf::Vector2i position) const;								// true if ship can be placed on a given position
	void draw_updated_shot_fields(sf::RenderWindow* window);						// draws dots and red ship tile textures 
	
	/* missile handling */
	Net::PlayerAction update_grid_after_ship_sank(Ship& ship, sf::Vector2i missilePos);	// updates grid after missile hit and caused ship sinking
	Net::PlayerAction update_grid_after_hit_part(sf::Vector2i missilePos);				// updating grid after missile hit a part of a ship
	Net::PlayerAction update_grid_after_hit_one(Ship& ship, sf::Vector2i missilePos);	// updating grid after missile hit a one lenght ship
	Net::PlayerAction update_shot_tiles(Ship* ship, sf::Vector2i missilePos);			// updates shot tiles depending on a missile accuracy, returns a PlayerAction which will be send back to the remote
};

