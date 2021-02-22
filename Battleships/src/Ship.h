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

public:
	Ship(void);
	Ship(const sf::Vector2f& headPosition, uint8_t shipLength, Orientation orientation, const sf::Texture &texture, bool** gridFields);
	~Ship(void);

	void move_ship(void);
	void draw_ship(sf::RenderWindow* window);
	void updateGridFields(sf::Vector2i shipSegment);
};

