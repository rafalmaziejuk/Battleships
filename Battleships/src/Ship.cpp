#include "Ship.h"
#include "Defines.h"

#include "Grid.h"
#include <iostream>

Ship::Ship(void) :
	mStart(),
	mEnd()
{
	if (mLength == 1)
		mOrientation = Orientation::Horizontal;
	else if (get_start().x == get_end().x)
		mOrientation = Orientation::Vertical;
	else mOrientation = Orientation::Horizontal;

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

bool Ship::contain_tile(const sf::Vector2i& cursorPos) const
{
	sf::Vector2i shift(0, 0);
	sf::Vector2i tilePos = (sf::Vector2i)mStart;
	//tilePos = invert_vector(tilePos);

	std::cout << "Curr:" << cursorPos.x << " " << cursorPos.y << "\n";
	std::cout << "tilePos:" << tilePos.x << " " << tilePos.y << "\n";

	if (mLength == 1)
	{
		if (tilePos == cursorPos)
			return true;
		else return false;
	}

	(mOrientation == Orientation::Horizontal) ? shift.y += 1 : shift.x += 1;

	for (unsigned i = 0; i < mLength; i++)
	{
		//std::cout << "Curr:" << cursorPos.x << " " << cursorPos.y << "\n";
		//std::cout << "tilePos:" << tilePos.x << " " << tilePos.y << "\n";
		if (tilePos == cursorPos)
			return true;
		tilePos += shift;
	}
	return false;
}