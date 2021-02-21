#include "Grid.h"
#include "ResourceManager.h"

Grid::Grid(sf::Vector2i &gridOrigin, const TextureManager &textures) :
	mGridOrigin(gridOrigin),
	mGridSprite(textures.get_resource(Textures::ID::GRID)),
	mCursor(textures.get_resource(Textures::ID::SELECTED_TILE))
{
	mGridSprite.setPosition(gridOrigin.x, gridOrigin.y);

	// adding ships
	mShips.push_back(Ship(sf::Vector2f(3.0f, 3.0f), 1, Orientation::Horizontal, textures.get_resource(Textures::ID::SHIP_TILE)));
	mShips.push_back(Ship(sf::Vector2f(5.0f, 5.0f), 2, Orientation::Horizontal, textures.get_resource(Textures::ID::SHIP_TILE)));
}

Grid::~Grid(void)
{

}

void Grid::draw(sf::RenderWindow *window) const
{
	window->draw(mGridSprite);

	
	//drawing ships
	for (auto i : mShips)
	{
		i.draw_ship(window);
	}

	if (mCursor.mDraw)
		window->draw(mCursor.mCursorSprite);
}

void Grid::update_cursor(sf::Vector2i mousePosition)
{
	if ((mousePosition.x > mGridOrigin.x + CELL_SIZE && mousePosition.y > mGridOrigin.y + CELL_SIZE) &&
		(mousePosition.x < mGridOrigin.x + CELL_SIZE * (FIELDS + 1) && mousePosition.y < mGridOrigin.y + CELL_SIZE * (FIELDS + 1)))
	{
		mousePosition.x /= CELL_SIZE;
		mousePosition.y /= CELL_SIZE;

		mCursor.set_position(sf::Vector2f(mousePosition.x, mousePosition.y));
		mCursor.mDraw = true;
	}
	else
		mCursor.mDraw = false;
}