#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.h"
#include "Defines.h"

class Ship;

enum class Type
{
	PLAYER,
	ENEMY
};


class Grid
{
private:

	sf::Texture mTileTexture;
	std::vector<sf::Sprite> mTileSprites;
	sf::Vector2i mGridStart;

private:
	bool mFields[FIELDS][FIELDS] = { false }; //fields taken overall
	bool mShipFields[FIELDS][FIELDS] = { false }; //fields occupied by ships only
	Type mType;

private:
	void update_fields(sf::Vector2i position);
	sf::Vector2i get_window_coordinates(sf::Vector2i position) const;

public:
	Grid(Type type, sf::Vector2i gridStart);
	~Grid(void);

	void draw(sf::RenderWindow *window) const;
	void update(const Ship &ship);

	void set_texture(const sf::Texture &texture);
	Type get_type(void) const;
	sf::Vector2i get_grid_coordinates(sf::Vector2i mousePosition) const;
	bool is_field_free(sf::Vector2i position) const;

};