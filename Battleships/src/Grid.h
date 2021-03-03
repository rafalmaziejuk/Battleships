#pragma once

#include "ResourceIdentifiers.h"
#include "ShipHint.h"
#include "Remote.h"
#include "Ship.h"

#include <SFML/Graphics.hpp>

class Ship;

// ship action that can be performed on the grid 
enum class ShipAction
{
	ADD,
	REMOVE
};

// tile status( NULL, tile HIT by missile, tile MISSED)
enum class TileStatus
{
	NUL,	// not fired yet 
	HIT,	// fired and hit
	MISS	// fired and missed
};

// Grid representation
class Grid
{
public:
	enum { FIELDS = 10, CELL_SIZE = 50 };

	bool mFields[FIELDS][FIELDS] = { false };						// fields taken overall
	bool mShipFields[FIELDS][FIELDS] = { false };					// fields occupied by ships only
	TileStatus mShotTiles[FIELDS][FIELDS] = { TileStatus::NUL };	// fields status table depending on missile accuracy

	Net::Remote* mRemote;		// remote pointer
	sf::Texture mTileTexture;	// ship tile texture
	sf::Vector2i mGridStart;	// grid start position on the window
	sf::Sprite mDotSprite;		// dot sprite
	sf::Sprite mSankShipTile;	// sank ship sprite
	ShipHint mShipHint;			// ship hint

	/* constructor / destructor */

	Grid(const sf::Vector2i gridStart);
	~Grid(void);

	/* initialization */

	void set_dot_testure(const sf::Texture& texture);							// sets dot sprite texture
	void set_ship_texture(const sf::Texture& texture);							// sets ship tile texture
	void set_sank_ship_texture(const sf::Texture& texture);						// sets sank ship tile texture
	void set_hint_ship_texture(sf::Texture& texture, sf::Texture& texture2);	// sets hint ship tile textures ( both active tile and innactive )
	void set_remote(Net::Remote* remote);										// sets pointer to the remote

	/* utility functions */

	sf::Vector2i get_grid_coordinates(sf::Vector2i mousePosition) const;		// returns this grid coordinates depending on mouse position
	sf::Vector2i get_window_coordinates(sf::Vector2i position) const;			// returns window coordinates depending on cursor position on the grid
	
};