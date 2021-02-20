#include "Grid.h"
#include "State.h"

Grid::Grid(sf::Vector2i &&gridOrigin) :
	mGridOrigin(gridOrigin),
	mTexture(),
	mSprite()
{
	mTexture.loadFromFile("assets/grid.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(gridOrigin.x, gridOrigin.y);
}

Grid::~Grid(void)
{

}

void Grid::draw(sf::RenderWindow *window) const
{
	window->draw(mSprite);

	if (mCursor.mDraw)
		window->draw(mCursor.mShape);
}

void Grid::update_cursor(sf::Vector2i mousePosition)
{
	if ((mousePosition.x > mGridOrigin.x + CELL_SIZE && mousePosition.y > mGridOrigin.y + CELL_SIZE) &&
		(mousePosition.x < mGridOrigin.x + CELL_SIZE * (FIELDS + 1) && mousePosition.y < mGridOrigin.y + CELL_SIZE * (FIELDS + 1)))
	{
		mousePosition.x /= CELL_SIZE;
		mousePosition.y /= CELL_SIZE;

		mCursor.setPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
		mCursor.mDraw = true;
	}
	else
		mCursor.mDraw = false;
}