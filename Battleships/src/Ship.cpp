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

///////////////////////////////////////////////////////////////

inline static sf::Vector2f invert_vector(sf::Vector2f vec)
{
	return sf::Vector2f(vec.y, vec.x);
}

inline static sf::Vector2i invert_vector(sf::Vector2i vec)
{
	return sf::Vector2i(vec.y, vec.x);
}


Ship::Ship(void) :
	mHeadPosition(),
	mTiles(),
	mShipLength(0),
	mOrientation(Orientation::Horizontal),
	mIsAlive(false)
{

}

Ship::Ship(const sf::Vector2f& headPosition, uint8_t shipLength, Orientation orientation, const sf::Texture &texture, bool** gridFields, bool** unavailableFields) :
	mHeadPosition(headPosition),
	mShipLength(shipLength),
	mOrientation(orientation),
	mIsAlive(true)
{
	/*
	for (uint8_t i = 0; i < shipLength; i++)
		mTiles.back().setPosition(mHeadPosition.x * CELL_SIZE, mHeadPosition.y * CELL_SIZE);
	*/

	mHeadPosition = invert_vector(mHeadPosition);
	// shifting to board position

	//tiles initialization
	sf::Vector2f shift(0.0f, 0.0f);

	for (uint8_t i = 0; i < shipLength; i++)
	{
		mTiles.push_back(sf::Sprite(texture));
		mTiles.back().setPosition((map_to_grid(mHeadPosition.x) + shift.x) * CELL_SIZE, (map_to_grid(mHeadPosition.y) + shift.y) * CELL_SIZE);
		
		update_grid_fields(sf::Vector2i(mHeadPosition.x + shift.x, mHeadPosition.y + shift.y),gridFields);
		update_unavailable_fields(sf::Vector2i(mHeadPosition.x + shift.x, mHeadPosition.y + shift.y), unavailableFields);

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

void Ship::update_grid_fields(sf::Vector2i&& shipSegment, bool** gridFields)
{
	sf::Vector2i vec = shipSegment;
	vec = invert_vector(vec);

	gridFields[(int)(vec.x)][(int)(vec.y)] = true;
}

void Ship::update_unavailable_fields(sf::Vector2i&& shipSegment, bool** gridFields)
{
	sf::Vector2i vec(shipSegment);

	// x-1,y-1 
	//
	//
	//gridFields[vec.x-1]
}