#include "Grid.h"

#include <iostream>

Grid::Grid(const sf::Vector2i gridStart) :
	mTileTexture(),
	mGridStart(gridStart),
	mShipHint(),
	mRemote(nullptr)
{
}

Grid::~Grid(void)
{
}

void Grid::set_dot_testure(const sf::Texture& texture)
{
	mDotSprite.setTexture(texture);
}

void Grid::set_ship_texture(const sf::Texture &texture)
{
	mTileTexture = texture;
}

void Grid::set_sank_ship_texture(const sf::Texture& texture)
{
	mSankShipTile.setTexture(texture);
}

void Grid::set_remote(Net::Remote* remote)
{
	mRemote = remote;
}

sf::Vector2i Grid::get_grid_coordinates(sf::Vector2i mousePosition) const
{
	mousePosition.x = (mousePosition.x - mGridStart.x) / CELL_SIZE;
	mousePosition.y = (mousePosition.y - mGridStart.y) / CELL_SIZE;

	return mousePosition;
}

sf::Vector2i Grid::get_window_coordinates(sf::Vector2i position) const
{
	position.x = position.x * CELL_SIZE + mGridStart.x;
	position.y = position.y * CELL_SIZE + mGridStart.y;

	return position;
}