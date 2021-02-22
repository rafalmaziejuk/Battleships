#include "Ship.h"
#include "Defines.h"
#include <iostream>

// used only for drawing Sprites!
// actual ship segment position is in range [(0..9)][(0..9)];

inline static float map_to_grid(float coord)
{
	return coord + 2.0f;
}

inline static sf::Vector2f map_to_grid(sf::Vector2f vec)
{
	return vec + sf::Vector2f(2, 2);
}

Ship::Ship(void) :
	mHeadPosition(),
	mTiles(),
	mShipLength(0),
	mOrientation(Orientation::Horizontal),
	mIsAlive(false)
{

}

Ship::Ship(const sf::Vector2f& headPosition, uint8_t shipLength, Orientation orientation, const sf::Texture &texture, bool** gridFields) :
	mHeadPosition(headPosition),
	mShipLength(shipLength),
	mOrientation(orientation),
	mIsAlive(true)
{
	/*
	for (uint8_t i = 0; i < shipLength; i++)
		mTiles.back().setPosition(mHeadPosition.x * CELL_SIZE, mHeadPosition.y * CELL_SIZE);
	*/

	// shifting to board position

	//tiles initialization
	sf::Vector2f shift(0.0f, 0.0f);

	for (uint8_t i = 0; i < shipLength; i++)
	{
		mTiles.push_back(sf::Sprite(texture));
		mTiles.back().setPosition((map_to_grid(mHeadPosition.x) + shift.x) * CELL_SIZE, (map_to_grid(mHeadPosition.y) + shift.y) * CELL_SIZE);
		gridFields[(int)(mHeadPosition.y + shift.y)][(int)(mHeadPosition.x + shift.x)] = true;
		//updating shift for the new segment position
		(mOrientation == Orientation::Horizontal) ? shift.x += 1.0f : shift.y += 1.0f;
		//std::cout << mTiles.back().getPosition().x << " " << mTiles.back().getPosition().y<<"\n";
	}
}

Ship::~Ship(void) 
{

}

void Ship::move_ship(void)
{

}

void Ship::draw_ship(sf::RenderWindow* window)
{
	for (auto& i : mTiles)
		window->draw(i);

	//window->draw(mTiles[3]);
}

void Ship::updateGridFields(void)
{

}