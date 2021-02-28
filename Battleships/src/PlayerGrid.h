#pragma once

#include "Grid.h"

class PlayerGrid : public Grid
{


private:
	void add_ship_to_grid(Ship& ship);
	void delete_ship_from_grid(Ship& ship);
	void update_ship_hint(const int shipId, HintAction action);
	void set_new_ship_segment(sf::Vector2i position, Ship& ship);
	void update_fields(sf::Vector2i position, bool somethingAdded);

public:
	unsigned mPlacedShips;

	PlayerGrid(sf::Vector2i gridStart);
	~PlayerGrid();

	void draw(sf::RenderWindow* window) const;
	void update(Ship& ship, ShipAction action);
	bool is_field_free(sf::Vector2i position) const;
};

