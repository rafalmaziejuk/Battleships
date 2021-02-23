#include "Grid.h"

#include "Ship.h"
#include "ConsoleDebug.h"

#include <iostream>

Grid::Grid(Type type, sf::Vector2i gridStart) :
	mTileTexture(),
	mGridStart(gridStart),
	mType(type)
{


}

Grid::~Grid(void)
{

	
}

void Grid::update_fields(sf::Vector2i position, bool somethingAdded)
{
	if(somethingAdded)
		mShipFields[position.y][position.x] = true;

	mFields[position.y - 1 < 0 ? position.y : position.y - 1][position.x - 1 < 0 ? position.x : position.x - 1] = true;
	mFields[position.y - 1 < 0 ? position.y : position.y - 1][position.x] = true;
	mFields[position.y - 1 < 0 ? position.y : position.y - 1][position.x + 1 == FIELDS ? position.x : position.x + 1] = true;
	mFields[position.y][position.x - 1 < 0 ? position.x : position.x - 1] = true;
	mFields[position.y][position.x] = true;
	mFields[position.y][position.x + 1 == FIELDS ? position.x : position.x + 1] = true;
	mFields[position.y + 1 == FIELDS ? position.y : position.y + 1][position.x - 1 < 0 ? position.x : position.x - 1] = true;
	mFields[position.y + 1 == FIELDS ? position.y : position.y + 1][position.x] = true;
	mFields[position.y + 1 == FIELDS ? position.y : position.y + 1][position.x + 1 == FIELDS ? position.x : position.x + 1] = true;
}

sf::Vector2i Grid::get_window_coordinates(sf::Vector2i position) const
{
	position.x = position.x * CELL_SIZE + mGridStart.x;
	position.y = position.y * CELL_SIZE + mGridStart.y;

	return position;
}


void Grid::draw(sf::RenderWindow *window) const
{
	//for (auto tile : mTileSprites)
		//window->draw(tile);

	// for debugging purpose only
		//////////////////////////////////////////////////

	
	console_cursor(false);
	std::cout << "GridFields\n";
	std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
	for (unsigned i = 0; i < FIELDS; i++)
	{
		std::cout << i << " ";
		for (unsigned j = 0; j < FIELDS; j++)
		{
			(mShipFields[i][j] == false) ? std::cout << ". " : std::cout << "x ";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
	std::cout << "UnavaliableFields\n";
	std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
	for (unsigned i = 0; i < FIELDS; i++)
	{
		std::cout << i << " ";
		for (unsigned j = 0; j < FIELDS; j++)
		{
			(mFields[i][j] == false) ? std::cout << ". " : std::cout << "x ";
		}
		std::cout << "\n";
	}
	cls();
	
	//////////////////////////////////////////////////
}


void Grid::update(Ship &ship,Action action)
{
	if (this->mType == Type::PLAYER)
	{
		if (action == Action::ADD)
		{
			add_ship_to_grid(ship);

		}
		else if (action == Action::REMOVE)
		{
			delete_ship_from_grid(ship);
		}
	}

	if (mType == Type::ENEMY)
	{
		//if(action == Action::??????)
		// { }
		//TODO(rm): Right grid update functionality
	}
}

void Grid::add_ship_to_grid(Ship& ship)
{
	sf::Vector2i start = ship.get_start();
	sf::Vector2i end = ship.get_end();
	sf::Vector2i position = start;

	if (start == end)
	{
		set_new_ship_segment(position, ship);
		ship.mDirection = Direction::Null;
		std::cout << position.x << " " << position.y << "\n";
	}
	else if (start.x == end.x)
	{
		ship.mOrientation = Orientation::Vertical;
		if (start.y > end.y)
		{
			ship.mDirection = Direction::Up;
			while (position.y >= end.y)
			{
				set_new_ship_segment(position, ship);
				std::cout << position.x << " " << position.y << "\n";
				position.y--;
			}
		}
		else if (start.y < end.y)
		{
			ship.mDirection = Direction::Down;
			while (position.y <= end.y)
			{
				set_new_ship_segment(position, ship);
				std::cout << position.x << " " << position.y << "\n";
				position.y++;
			}
		}
	}
	else if (start.y == end.y)
	{
		ship.mOrientation = Orientation::Horizontal;
		if (start.x > end.x)
		{
			ship.mDirection = Direction::Left;
			while (position.x >= end.x)
			{
				set_new_ship_segment(position, ship);
				std::cout << position.x << " " << position.y << "\n";
				position.x--;
			}
		}
		else if (start.x < end.x)
		{
			ship.mDirection = Direction::Right;
			while (position.x <= end.x)
			{
				set_new_ship_segment(position, ship);
				std::cout << position.x << " " << position.y << "\n";
				position.x++;
			}
		}
	}
}

void Grid::delete_ship_from_grid(Ship& ship)
{
	ship.mIsOnGrid = false;
	ship.remove_tiles();

	//mShipFields[][] = false;
	sf::Vector2i shift(0, 0);

	for (unsigned i = 0; i < ship.get_length(); i++)
	{
		mShipFields[ship.get_start().y + shift.y][ship.get_start().x + shift.x] = false;
		switch (ship.mDirection)
		{
			case Direction::Left:	shift.x -= 1;	break;
			case Direction::Right:	shift.x += 1;	break;
			case Direction::Up:		shift.y -= 1;	break;
			case Direction::Down:	shift.y += 1;	break;
		}
		//(ship.get_orientation() == Orientation::Horizontal) ? shift.x++ : shift.y++;
	}

	for (unsigned i = 0; i < FIELDS; i++)
	{
		for (unsigned j = 0; j < FIELDS; j++)
		{
			mFields[i][j] = false;
		}
	}
	
	for (unsigned i = 0; i < FIELDS; i++)
	{
		for (unsigned j = 0; j < FIELDS; j++)
			if (mShipFields[i][j] == true)
				update_fields(sf::Vector2i(j, i),false);
			
	}
}

void Grid::set_new_ship_segment(sf::Vector2i position, Ship& ship)
{
	sf::Sprite newTile(mTileTexture);
	update_fields(position,true);
	newTile.setPosition(sf::Vector2f(get_window_coordinates(position)));
	ship.getShipTiles().push_back(newTile);
}

void Grid::set_texture(const sf::Texture &texture)
{
	mTileTexture = texture;
}

Type Grid::get_type(void) const
{
	return mType;
}

sf::Vector2i Grid::get_grid_coordinates(sf::Vector2i mousePosition) const
{
	mousePosition.x = (mousePosition.x - mGridStart.x) / CELL_SIZE;
	mousePosition.y = (mousePosition.y - mGridStart.y) / CELL_SIZE;

	return mousePosition;
}

bool Grid::is_field_free(sf::Vector2i position) const
{
	return !mFields[position.y][position.x];
}


