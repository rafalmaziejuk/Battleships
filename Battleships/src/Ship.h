#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class Orientation
{
	Horizontal, Vertical
};

class Ship
{
private:
	std::vector<sf::Sprite> mTiles;
	sf::Vector2f mHeadPosition;

private:
	uint8_t mShipLength;
	Orientation mOrientation;
	bool mIsAlive;
	short mID;

	void update_grid_fields(sf::Vector2i&& shipSegment, bool** gridFields);
	void update_unavailable_fields(sf::Vector2i&& shipSegment, bool** gridFields, bool** unavailableFields);
	void update_unavailable_fields(bool** gridFields, bool** unavailableFields);
	void update_tile_area(const sf::Vector2i& pos, bool** unavailableFields);
public:
	Ship(void);
	Ship(short id, const sf::Vector2f& headPosition, uint8_t shipLength, Orientation orientation, const sf::Texture &texture, bool** gridFields, bool** unavailableFields);
	~Ship(void);

	void move_ship(const sf::Vector2f& pos);
	void set_position(const sf::Vector2i& pos);
	void draw_ship(sf::RenderWindow* window);
	void change_orientation(void);
	bool contain_tile(const sf::Vector2i& cursorPos);
};

