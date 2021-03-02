#include "Ship.h"
#include "Grid.h"

#include <iostream>

Ship::Ship(void) :
	mStart(),
	mEnd(),
	mDirection(Direction::Null),
	mHitTiles(0),
	mSank(false)
{
	static int id = 0;
	mId = id;
	id++;
}

Ship::Ship(uint8_t lenght) :
	mStart(),
	mEnd(),
	mDirection(Direction::Null),
	mHitTiles(0),
	mSank(false),
	mLength(lenght)
{
	static int id = 0;
	mId = id;
	id++;
}

Ship::~Ship(void) 
{

}

void Ship::remove_tiles(void)
{
	mTiles.clear();
}

void Ship::draw_ship(sf::RenderWindow* window) const
{
	if (!mSank)
	{
		for (auto& i : mTiles)
		{
			window->draw(i);
		}
	}
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

void Ship::reset(void)
{
	mSank = false;
	mIsOnGrid = false;
	mTiles.clear();
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

std::vector<sf::Sprite>& Ship::getShipTiles(void)
{
	return mTiles;
}

bool Ship::contain_tile(const sf::Vector2i& cursorPos) const
{
	sf::Vector2i shift(0, 0);
	sf::Vector2i tilePos = sf::Vector2i(mStart.x,mStart.y);
	
	if (mLength == 1)
	{
		if (tilePos == cursorPos)
			return true;
		else return false;
	}

	switch (mDirection)
	{
		case Direction::Left:	shift.x -= 1;	break;
		case Direction::Right:	shift.x += 1;	break;
		case Direction::Up:		shift.y -= 1;	break;
		case Direction::Down:	shift.y += 1;	break;
	}

	for (unsigned i = 0; i < mLength; i++)
	{
		if (tilePos == cursorPos)
			return true;
		tilePos += shift;
		
	}
	return false;
}

Orientation Ship::get_orientation(void) const
{
	return mOrientation;
}