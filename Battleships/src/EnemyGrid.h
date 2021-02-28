#pragma once

#include "Grid.h"

class EnemyGrid : public Grid
{

public:
	unsigned mHitShips;

	EnemyGrid(const sf::Vector2i gridStart);
	~EnemyGrid();
};

