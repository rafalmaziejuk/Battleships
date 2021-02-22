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

Ship::Ship(short id, const sf::Vector2f& headPosition, uint8_t shipLength, Orientation orientation, const sf::Texture& texture, bool** gridFields, bool** unavailableFields) :

	mHeadPosition(headPosition),
	mShipLength(shipLength),
	mOrientation(orientation),
	mIsAlive(true),
	mID(id)
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


		update_grid_fields(sf::Vector2i(mHeadPosition.x + shift.x, mHeadPosition.y + shift.y), gridFields);
		update_unavailable_fields(sf::Vector2i(mHeadPosition.x + shift.x, mHeadPosition.y + shift.y), gridFields, unavailableFields);

		//updating shift for the new segment position
		(mOrientation == Orientation::Horizontal) ? shift.x += 1.0f : shift.y += 1.0f;
		//std::cout << mTiles.back().getPosition().x << " " << mTiles.back().getPosition().y<<"\n";
	}
}

Ship::~Ship(void) 
{

}

void Ship::move_ship(const sf::Vector2f& pos)
{
	
}

void Ship::set_position(const sf::Vector2i& pos)
{
	unsigned tileNr = 0;
	for (auto& i : mTiles)
	{
		i.setOrigin(25.0f, 25.0f);
		if (mOrientation == Orientation::Vertical)
		{
			i.setPosition(sf::Vector2f(pos.x, pos.y + 50 *tileNr));
		}
		else if (mOrientation == Orientation::Horizontal)
		{
			i.setPosition(sf::Vector2f(pos.x + 50 * tileNr, pos.y));
		}
		tileNr++;
	}
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


// updates tile area when inserting new ship
void Ship::update_unavailable_fields(sf::Vector2i&& shipSegment, bool** gridFields, bool** unavailableFields)
{
	sf::Vector2i v(shipSegment);
	v = invert_vector(v);

	// x-1,y-1	x-1 y	x-1 y+1
	// x ,y-1	x y		x y+1
	//x+1,y-1	x+1,y	x+1,y+1
	update_tile_area(v, unavailableFields);
	
}

// updates tile area every time a change in ship position appears 
void Ship::update_unavailable_fields(bool** gridFields, bool** unavailableFields)
{
	for (unsigned i = 0; i < FIELDS; i++)
	{
		for (unsigned j = 0; j < FIELDS; j++)
		{
			// a tile exist on this place
			if (gridFields[i][j] == true)
				update_tile_area(sf::Vector2i(i, j), unavailableFields);
		}
	}
}


void Ship::update_tile_area(const sf::Vector2i& pos,bool** unavailableFields)
{
	unavailableFields[(pos.x - 1 >= 0 && pos.x - 1 < FIELDS) ? pos.x - 1 : pos.x][(pos.y - 1 >= 0 && pos.y - 1 < FIELDS) ? pos.y - 1 : pos.y] = true;
	unavailableFields[(pos.x - 1 >= 0 && pos.x - 1 < FIELDS) ? pos.x - 1 : pos.x][pos.y] = true;
	unavailableFields[(pos.x - 1 >= 0 && pos.x - 1 < FIELDS) ? pos.x - 1 : pos.x][(pos.y + 1 >= 0 && pos.y + 1 < FIELDS) ? pos.y + 1 : pos.y] = true;
	unavailableFields[pos.x][(pos.y - 1 >= 0 && pos.y - 1 < FIELDS) ? pos.y - 1 : pos.y] = true;
	unavailableFields[pos.x][pos.y] = true;
	unavailableFields[pos.x][(pos.y + 1 >= 0 && pos.y + 1 < FIELDS) ? pos.y + 1 : pos.y] = true;
	unavailableFields[(pos.x + 1 >= 0 && pos.x + 1 < FIELDS) ? pos.x + 1 : pos.x][(pos.y - 1 >= 0 && pos.y - 1 < FIELDS) ? pos.y - 1 : pos.y] = true;
	unavailableFields[(pos.x + 1 >= 0 && pos.x + 1 < FIELDS) ? pos.x + 1 : pos.x][pos.y] = true;
	unavailableFields[(pos.x + 1 >= 0 && pos.x + 1 < FIELDS) ? pos.x + 1 : pos.x][(pos.y + 1 >= 0 && pos.y + 1 < FIELDS) ? pos.y + 1 : pos.y] = true;
}

void Ship::change_orientation(void)
{

}

bool Ship::contain_tile(const sf::Vector2i& cursorPos)
{
	sf::Vector2i shift(0, 0);
	sf::Vector2i tilePos = (sf::Vector2i)mHeadPosition;
	tilePos = invert_vector(tilePos);

	//std::cout << "Curr:" << cursorPos.x << " " << cursorPos.y << "\n";
	//std::cout << "tilePos:" << tilePos.x << " " << tilePos.y << "\n";

	if (mShipLength == 1)
	{
		if (tilePos == cursorPos)
			return true;
		else return false;
	}

	(mOrientation == Orientation::Horizontal) ? shift.y += 1.0f : shift.x += 1.0f;

	for (unsigned i = 0; i < mShipLength; i++)
	{
		//std::cout << "Curr:" << cursorPos.x << " " << cursorPos.y << "\n";
		//std::cout << "tilePos:" << tilePos.x << " " << tilePos.y << "\n";
		if (tilePos == cursorPos)
			return true;
		tilePos += shift;
	}
	return false;
}