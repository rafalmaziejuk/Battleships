#pragma once

#include "ResourceIdentifiers.h"
#include "ShipHint.h"
#include "Remote.h"
#include "Ship.h"

#include <SFML/Graphics.hpp>

class Ship;

enum class ShipAction
{
	ADD,
	REMOVE
};

class Grid
{
public:
	enum { FIELDS = 10, CELL_SIZE = 50 };

	bool mFields[FIELDS][FIELDS] = { false }; //fields taken overall
	bool mShipFields[FIELDS][FIELDS] = { false }; //fields occupied by ships only

	Net::Remote* mRemote;
	sf::Texture mTileTexture;
	sf::Vector2i mGridStart;
	ShipHint mShipHint;

	Grid(const sf::Vector2i gridStart);
	~Grid(void);

	sf::Vector2i get_grid_coordinates(sf::Vector2i mousePosition) const;
	sf::Vector2i get_window_coordinates(sf::Vector2i position) const;
	void set_ship_texture(const sf::Texture &texture);
	void set_hint_ship_texture(sf::Texture &texture, sf::Texture& texture2);
	void set_remote(Net::Remote* remote);

};