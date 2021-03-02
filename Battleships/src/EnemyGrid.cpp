#include "EnemyGrid.h"

#include <list>

EnemyGrid::EnemyGrid(const sf::Vector2i gridStart)
	: Grid(gridStart)
{
}

EnemyGrid::~EnemyGrid()
{

}

void EnemyGrid::draw(sf::RenderWindow* window)
{
	draw_dots(window);
}

void EnemyGrid::reset(void)
{
	for (unsigned i = 0; i < FIELDS; i++)
	{
		for (unsigned j = 0; j < FIELDS; j++)
		{
			mShotTiles[i][j] = TileStatus::NUL;
		}
	}
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
				mDotSprite.setPosition(sf::Vector2f((float)(mGridStart.x + i * 50), (float)(mGridStart.y + j * 50)));
				window->draw(mDotSprite);
			}
			
			if (mShotTiles[i][j] == TileStatus::HIT)
			{
				mSankShipTile.setPosition(sf::Vector2f((float)(mGridStart.x + i * 50), (float)(mGridStart.y + j * 50)));
				window->draw(mSankShipTile);
			}
		}
	}
}

// to be rafactored
void EnemyGrid::update_grid_after_ship_sank(sf::Vector2i missilePos, sf::Vector2i comeFrom)
{
	
	std::list<sf::Vector2i> tiles_to_update;
	/*
	for (int x = 0; x < FIELDS; x++)
	{
		for (int  y = 0; y < FIELDS; y++)
		{
			if (mShotTiles[x][y] == TileStatus::HIT)
			{
				if (x - 1 >= 0 && y - 1 >= 0)
					if(mShotTiles[x - 1][y - 1] != TileStatus::HIT)
						tiles_to_update.push_back(sf::Vector2i(x - 1, y - 1));
				if (x - 1 >= 0)
					if(mShotTiles[x - 1][y] != TileStatus::HIT)								
						tiles_to_update.push_back(sf::Vector2i(x - 1, y));

				if (x - 1 >= 0 && y + 1 < FIELDS)
					if(mShotTiles[x - 1][y + 1] != TileStatus::HIT)		
						tiles_to_update.push_back(sf::Vector2i(x - 1, y + 1));

				if (y - 1 >= 0)
					if(mShotTiles[x][y - 1] != TileStatus::HIT)								
						tiles_to_update.push_back(sf::Vector2i(x, y - 1));
				if (y + 1 < FIELDS )
					if(mShotTiles[x][y + 1] != TileStatus::HIT)							
						tiles_to_update.push_back(sf::Vector2i(x, y + 1));
				if (x + 1 < FIELDS && y - 1 >= 0 )
					if(mShotTiles[x + 1][y - 1] != TileStatus::HIT)		
						tiles_to_update.push_back(sf::Vector2i(x + 1, y - 1));
				if (x + 1 < FIELDS)
					if(mShotTiles[x+ 1][y] != TileStatus::HIT)							
						tiles_to_update.push_back(sf::Vector2i(x + 1, y));
				if (x + 1 < FIELDS && y + 1 < FIELDS)
					if(mShotTiles[x + 1][y + 1] != TileStatus::HIT)	
						tiles_to_update.push_back(sf::Vector2i(x + 1, y + 1));
						
			}
		}
	}
	*/
	int x = missilePos.x;
	int y = missilePos.y;

	if (mShotTiles[x][y] == TileStatus::HIT)
	{
		if (x - 1 >= 0 && y - 1 >= 0)
		{
			if (mShotTiles[x - 1][y - 1] != TileStatus::HIT)
				tiles_to_update.push_back(sf::Vector2i(x - 1, y - 1));
			else if (comeFrom != sf::Vector2i(x - 1, y - 1))
				update_grid_after_ship_sank(sf::Vector2i(x - 1, y - 1), missilePos);
		}
		if (x - 1 >= 0)
		{
			if (mShotTiles[x - 1][y] != TileStatus::HIT)
				tiles_to_update.push_back(sf::Vector2i(x - 1, y));
			else if (comeFrom != sf::Vector2i(x - 1, y))
				update_grid_after_ship_sank(sf::Vector2i(x - 1, y), missilePos);
		}
		if (x - 1 >= 0 && y + 1 < FIELDS)
		{
			if (mShotTiles[x - 1][y + 1] != TileStatus::HIT)
				tiles_to_update.push_back(sf::Vector2i(x - 1, y + 1));
			else if(comeFrom != sf::Vector2i(x - 1, y + 1))
				update_grid_after_ship_sank(sf::Vector2i(x - 1, y + 1), missilePos);
		}
		if (y - 1 >= 0)
		{
			if (mShotTiles[x][y - 1] != TileStatus::HIT)
				tiles_to_update.push_back(sf::Vector2i(x, y - 1));
			else if(comeFrom != sf::Vector2i(x, y - 1))
				update_grid_after_ship_sank(sf::Vector2i(x, y - 1), missilePos);
		}
		if (y + 1 < FIELDS)
		{
			if (mShotTiles[x][y + 1] != TileStatus::HIT)
				tiles_to_update.push_back(sf::Vector2i(x, y + 1));
			else if(comeFrom != sf::Vector2i(x, y + 1))
				update_grid_after_ship_sank(sf::Vector2i(x, y + 1), missilePos);
		}
		if (x + 1 < FIELDS && y - 1 >= 0)
		{
			if (mShotTiles[x + 1][y - 1] != TileStatus::HIT)
				tiles_to_update.push_back(sf::Vector2i(x + 1, y - 1));
			else if(comeFrom != sf::Vector2i(x + 1, y - 1)) 
				update_grid_after_ship_sank(sf::Vector2i(x + 1, y - 1), missilePos);
		}
		if (x + 1 < FIELDS)
		{
			if (mShotTiles[x + 1][y] != TileStatus::HIT)
				tiles_to_update.push_back(sf::Vector2i(x + 1, y));
			else if(comeFrom != sf::Vector2i(x + 1, y))
				update_grid_after_ship_sank(sf::Vector2i(x + 1, y), missilePos);
		}
		if (x + 1 < FIELDS && y + 1 < FIELDS)
		{
			if (mShotTiles[x + 1][y + 1] != TileStatus::HIT)
				tiles_to_update.push_back(sf::Vector2i(x + 1, y + 1));
			else if(comeFrom != sf::Vector2i(x + 1, y + 1))
				update_grid_after_ship_sank(sf::Vector2i(x + 1, y + 1), missilePos);
		}
	}

	for (auto& tile : tiles_to_update)
		mShotTiles[tile.x][tile.y] = TileStatus::MISS; // MISS means a dot is beign drawn
		
}

void EnemyGrid::update_shot_tiles(Net::PlayerAction action, sf::Vector2i missilePos)
{
	// setting coord to draw a HIT tile
	mShotTiles[missilePos.x][missilePos.y] = TileStatus::HIT;
	std::list<sf::Vector2i> tiles_to_update;

	if (action == Net::PlayerAction::HIT_ONE) // Hit ship with lenght 1
	{
		// im updating all possible coords around this tile and store in a vector
		if (missilePos.x - 1 >= 0 && missilePos.y - 1 >= 0)			tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1, missilePos.y - 1));
		if (missilePos.x - 1 >= 0)									tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1, missilePos.y));
		if (missilePos.x - 1 >= 0 && missilePos.y + 1 < FIELDS)		tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1, missilePos.y + 1));
		if (missilePos.y - 1 >= 0)									tiles_to_update.push_back(sf::Vector2i(missilePos.x, missilePos.y - 1));
		if (missilePos.y + 1 < FIELDS)								tiles_to_update.push_back(sf::Vector2i(missilePos.x, missilePos.y + 1));
		if (missilePos.x + 1 < FIELDS && missilePos.y - 1 >= 0)		tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y - 1));
		if (missilePos.x + 1 < FIELDS)								tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y));
		if (missilePos.x + 1 < FIELDS && missilePos.y + 1 < FIELDS)	tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y + 1));

		// updating mShotTiles with coords stored in vector
		
	}
	else if (action == Net::PlayerAction::HIT_PART)
	{
		if (missilePos.x - 1 >= 0 && missilePos.y - 1 >= 0)			tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1, missilePos.y - 1));
		if (missilePos.x - 1 >= 0 && missilePos.y + 1 < FIELDS)		tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1, missilePos.y + 1));
		if (missilePos.x + 1 < FIELDS && missilePos.y - 1 >= 0)		tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y - 1));
		if (missilePos.x + 1 < FIELDS && missilePos.y + 1 < FIELDS)	tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y + 1));

	}
	else if (action == Net::PlayerAction::HIT_AND_SANK)
	{
		update_grid_after_ship_sank(missilePos, sf::Vector2i(-1,-1));
	}

	for (auto& tile : tiles_to_update)
	{
		mShotTiles[tile.x][tile.y] = TileStatus::MISS; // MISS means a dot is beign drawn
		std::cout << "DOT ADDED\n";
	}
}