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

enum class Action
{
	ADD,
	REMOVE
};

class Grid
{
private:

	sf::Texture mTileTexture;
	//std::vector<sf::Sprite> mTileSprites;
	sf::Vector2i mGridStart;

private:
	bool mFields[FIELDS][FIELDS] = { false }; //fields taken overall
	bool mShipFields[FIELDS][FIELDS] = { false }; //fields occupied by ships only
	Type mType;

private:
	void update_fields(sf::Vector2i position, bool somethingAdded);
	sf::Vector2i get_window_coordinates(sf::Vector2i position) const;
	void set_new_ship_segment(sf::Vector2i position, Ship& ship);
	void add_ship_to_grid(Ship& ship);
	void delete_ship_from_grid(Ship& ship);

public:
	Grid(Type type, sf::Vector2i gridStart);
	~Grid(void);

	void draw(sf::RenderWindow *window) const;
	void update(Ship &ship,Action action);

	void set_texture(const sf::Texture &texture);
	Type get_type(void) const;
	sf::Vector2i get_grid_coordinates(sf::Vector2i mousePosition) const;
	bool is_field_free(sf::Vector2i position) const;

};