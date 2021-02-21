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
	static const int CELL_SIZE = 50;
	static const int FIELDS = 10;
	static const int GRID_SIZE = CELL_SIZE * (FIELDS + 1);

private:
	
	sf::Vector2f mHeadPosition;
	std::vector<sf::Sprite> mTiles;

	uint8_t mShipLength;
	Orientation mOrientation;
	bool mIsAlive;

public:
	Ship(sf::Vector2f headPosition, uint8_t shipLength, Orientation orientation, const sf::Texture &texture);
	~Ship(void);

	void move_ship(void);
	void draw_ship(sf::RenderWindow* window);
};

