#include "Grid.h"

#include "Ship.h"
#include <iostream>

Grid::Grid(Type type, sf::Vector2i gridStart) :
	mTileTexture(),
	mTileSprites(),
	mGridStart(gridStart),
	mType(type)
{


}

Grid::~Grid(void)
{

	
}

void Grid::update_fields(sf::Vector2i position)
{
	mFields[position.y - 1 < 0 ? position.y : position.y - 1][position.x - 1 < 0 ? position.x : position.x - 1] = true;
	mFields[position.y - 1 < 0 ? position.y : position.y - 1][position.x] = true;
	mFields[position.y - 1 < 0 ? position.y : position.y - 1][position.x + 1 == FIELDS ? position.x : position.x + 1] = true;
	mFields[position.y][position.x - 1 < 0 ? position.x : position.x - 1] = true;
	mFields[position.y][position.x] = true;
	mShipFields[position.y][position.x] = true;
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
	for (auto tile : mTileSprites)
		window->draw(tile);
}


void Grid::update(const Ship &ship)
{
	if (this->mType == Type::PLAYER)
	{
		sf::Vector2i start = ship.get_start();
		sf::Vector2i end = ship.get_end();
		sf::Vector2i position = start;
		sf::Sprite newTile(mTileTexture);

		if (start == end)
		{
			newTile.setPosition(sf::Vector2f(get_window_coordinates(position)));
			mTileSprites.push_back(newTile);
			update_fields(position);
		}
		else if (start.x == end.x)
		{
			if (start.y > end.y)
			{
				while (position.y >= end.y)
				{
					update_fields(position);
					newTile.setPosition(sf::Vector2f(get_window_coordinates(position)));
					mTileSprites.push_back(newTile);
					position.y--;
				}
			}
			else if (start.y < end.y)
			{
				while (position.y <= end.y)
				{
					update_fields(position);
					newTile.setPosition(sf::Vector2f(get_window_coordinates(position)));
					mTileSprites.push_back(newTile);
					position.y++;
				}
			}
		}
		else if (start.y == end.y)
		{
			if (start.x > end.x)
			{
				while (position.x >= end.x)
				{
					update_fields(position);
					newTile.setPosition(sf::Vector2f(get_window_coordinates(position)));
					mTileSprites.push_back(newTile);
					position.x--;
				}
			}
			else if (start.x < end.x)
			{
				while (position.x <= end.x)
				{
					update_fields(position);
					newTile.setPosition(sf::Vector2f(get_window_coordinates(position)));
					mTileSprites.push_back(newTile);
					position.x++;
				}
			}
		}
	}

	if (mType == Type::ENEMY)
	{
		//TODO(rm): Right grid update functionality
	}
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

