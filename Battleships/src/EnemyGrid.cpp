#include "EnemyGrid.h"

EnemyGrid::EnemyGrid(const sf::Vector2i gridStart)
	: Grid(gridStart), mHitShips(0)
{
}

EnemyGrid::~EnemyGrid()
{

}

void EnemyGrid::draw(sf::RenderWindow* window)
{
	draw_dots(window);
}

void EnemyGrid::update(void)
{

}

void EnemyGrid::fire_missile(const sf::Vector2i position)
{
	std::cout << "Missile fired to " << position.x << " " << position.y;
}

void EnemyGrid::draw_dots(sf::RenderWindow* window)
{
	for (unsigned i = 0; i < FIELDS; i++)
	{
		for (unsigned j = 0; j < FIELDS; j++)
		{
			if (mShotTiles[i][j] == TileStatus::MISS)
			{
				mDotSprite.setPosition(sf::Vector2f(mGridStart.x + i * 50, mGridStart.y + j * 50));
				window->draw(mDotSprite);
			}
			
			if (mShotTiles[i][j] == TileStatus::HIT)
			{
				mSankShipTile.setPosition(sf::Vector2f(mGridStart.x + i * 50, mGridStart.y + j * 50));
				window->draw(mSankShipTile);
			}
		}
	}
}