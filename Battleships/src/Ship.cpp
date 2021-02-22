#include "Ship.h"
#include "Defines.h"
#include "Grid.h"
#include <iostream>

Ship::Ship(void) :
	mStart(),
	mEnd()
{

}

Ship::~Ship(void) 
{

}

void Ship::set_length(uint8_t length)
{
	mLength = length;
}

void Ship::set_position(sf::Vector2i start, sf::Vector2i end)
{
	mStart = start;
	mEnd = end;
	mIsOnGrid = true;
}

sf::Vector2i Ship::get_start(void) const
{
	return mStart;
}

sf::Vector2i Ship::get_end(void) const
{
	return mEnd;
}

uint8_t Ship::get_length(void) const
{
	return mLength;
}

bool Ship::is_on_grid(void) const
{
	return mIsOnGrid;
}