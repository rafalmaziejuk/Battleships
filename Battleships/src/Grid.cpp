#include "Grid.h"

Grid::Grid(sf::Vector2i &&gridOrigin) :
	mGridOrigin(gridOrigin),
	mTexture(),
	mSprite(),
	mCursor()
{
	mTexture.loadFromFile("assets/grid.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(gridOrigin.x, gridOrigin.y);
	mCursor.setFillColor(sf::Color::Cyan);
	mCursor.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	mCursor.setPosition(sf::Vector2f(-CELL_SIZE, -CELL_SIZE));
}

Grid::~Grid(void)
{

}

void Grid::draw(sf::RenderWindow *window) const
{
	window->draw(mSprite);
}

void Grid::set_cursor_position(sf::Vector2f mousePosition)
{

}