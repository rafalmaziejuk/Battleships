#include "PlayerGrid.h"

#include <list>

PlayerGrid::PlayerGrid(sf::Vector2i gridStart)
	: Grid(gridStart), mPlacedShips(0)
{

}

PlayerGrid::~PlayerGrid()
{

}

void PlayerGrid::add_ship_to_grid(Ship& ship)
{
	sf::Vector2i start = ship.get_start();
	sf::Vector2i end = ship.get_end();
	sf::Vector2i position = start;

	mPlacedShips++;

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
	update_ship_hint(ship.mId, HintAction::ADD);
}

void PlayerGrid::delete_ship_from_grid(Ship& ship)
{
	ship.mIsOnGrid = false;
	ship.remove_tiles();

	mPlacedShips--;

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
				update_fields(sf::Vector2i(j, i), false);

	}
	update_ship_hint(ship.mId, HintAction::REMOVE);
}

void PlayerGrid::update_ship_hint(const int shipId, HintAction action)
{
	if (action == HintAction::ADD)
		mShipHint.update_ship_hints(shipId, HintAction::ADD);
	else if (action == HintAction::REMOVE)
		mShipHint.update_ship_hints(shipId, HintAction::REMOVE);
}

void PlayerGrid::set_new_ship_segment(sf::Vector2i position, Ship& ship)
{
	sf::Sprite newTile(mTileTexture);
	update_fields(position, true);
	newTile.setPosition(sf::Vector2f(get_window_coordinates(position)));
	ship.getShipTiles().push_back(newTile);
}

void PlayerGrid::update_fields(sf::Vector2i position, bool somethingAdded)
{
	if (somethingAdded)
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

void PlayerGrid::draw(sf::RenderWindow* window)
{
	//for (auto tile : mTileSprites)
		//window->draw(tile);

	// for debugging purpose only
		//////////////////////////////////////////////////
	mShipHint.draw_ship_hints(window);
	draw_dots(window);

	/*
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
	*/
	//////////////////////////////////////////////////
}


void PlayerGrid::update(Ship& ship, ShipAction action)
{
	if (action == ShipAction::ADD)
	{
		add_ship_to_grid(ship);

	}
	else if (action == ShipAction::REMOVE)
	{
		delete_ship_from_grid(ship);
	}
}

bool PlayerGrid::is_field_free(sf::Vector2i position) const
{
	return !mFields[position.y][position.x];
}

void PlayerGrid::draw_dots(sf::RenderWindow* window)
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
			else if (mShotTiles[i][j] == TileStatus::HIT)
			{
				mSankShipTile.setPosition(sf::Vector2f(mGridStart.x + i * 50, mGridStart.y + j * 50));
				window->draw(mSankShipTile);
			}
		}
	}
}

void PlayerGrid::update_grid_after_ship_sank(const Ship& ship, sf::Vector2i missilePos)
{
	std::list<sf::Vector2i> tiles_to_update;
	sf::Vector2i shift(0, 0);

	switch (ship.mDirection)
	{
		case Direction::Left:	shift.x -= 1;	break;
		case Direction::Right:	shift.x += 1;	break;
		case Direction::Up:		shift.y -= 1;	break;
		case Direction::Down:	shift.y += 1;	break;
	}

	sf::Vector2i pos = ship.get_start();

	for (unsigned i = 0; i < ship.get_length() ; i++)
	{	
		if (pos.x - 1 >= 0 && pos.y - 1 >= 0 && mShotTiles[pos.x -1 ][pos.y - 1] != TileStatus::HIT)				tiles_to_update.push_back(sf::Vector2i(pos.x - 1, pos.y - 1));
		if (pos.x - 1 >= 0 && mShotTiles[pos.x - 1][pos.y] != TileStatus::HIT)										tiles_to_update.push_back(sf::Vector2i(pos.x - 1, pos.y));
		if (pos.x - 1 >= 0 && pos.y + 1 < FIELDS && mShotTiles[pos.x - 1][pos.y + 1] != TileStatus::HIT)			tiles_to_update.push_back(sf::Vector2i(pos.x - 1, pos.y + 1));
		if (pos.y - 1 >= 0 && mShotTiles[pos.x][pos.y - 1] != TileStatus::HIT)										tiles_to_update.push_back(sf::Vector2i(pos.x, pos.y - 1));
		if (pos.y + 1 < FIELDS && mShotTiles[pos.x][pos.y + 1] != TileStatus::HIT)									tiles_to_update.push_back(sf::Vector2i(pos.x, pos.y + 1));
		if (pos.x + 1 < FIELDS && pos.y - 1 >= 0 && mShotTiles[pos.x + 1][pos.y - 1] != TileStatus::HIT)			tiles_to_update.push_back(sf::Vector2i(pos.x + 1, pos.y - 1));
		if (pos.x + 1 < FIELDS && mShotTiles[pos.x + 1][pos.y] != TileStatus::HIT)									tiles_to_update.push_back(sf::Vector2i(pos.x + 1, pos.y));
		if (pos.x + 1 < FIELDS && pos.y + 1 < FIELDS && mShotTiles[pos.x + 1][pos.y + 1] != TileStatus::HIT)		tiles_to_update.push_back(sf::Vector2i(pos.x + 1, pos.y + 1));
		mShotTiles[pos.x][pos.y] = TileStatus::HIT;
		pos += shift;
	}
	int counter = 0;
	for (auto& tile : tiles_to_update)
	{
		mShotTiles[tile.x][tile.y] = TileStatus::MISS; // MISS means a dot is beign drawn
		counter++;
	}
	std::cout << " \n\n " << counter << " DOTS DRAWN\n\n";
}

// function is called to update PLAYER GRID after his ship is hit

Net::PlayerAction PlayerGrid::update_shot_tiles(Ship* ship, sf::Vector2i missilePos)
{
	// setting coord to draw a HIT tile
	mShotTiles[missilePos.x][missilePos.y] = TileStatus::HIT;
	Net::PlayerAction playerAction = Net::PlayerAction::NUL;
	std::list<sf::Vector2i> tiles_to_update;

	if (ship->get_length() == 1) // Hit ship with lenght 1
	{
		// im updating all possible coords around this tile and store in a vector
		if (missilePos.x - 1 >= 0 && missilePos.y - 1 >= 0)			tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1, missilePos.y - 1));
		if (missilePos.x - 1  >= 0)									tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1 , missilePos.y ));
		if (missilePos.x - 1 >= 0 && missilePos.y + 1 < FIELDS)		tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1 , missilePos.y + 1));
		if (missilePos.y - 1  >= 0)									tiles_to_update.push_back(sf::Vector2i(missilePos.x , missilePos.y - 1));
		if (missilePos.y + 1  < FIELDS)								tiles_to_update.push_back(sf::Vector2i(missilePos.x , missilePos.y + 1));
		if (missilePos.x + 1 < FIELDS && missilePos.y - 1 >= 0)		tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y - 1));
		if (missilePos.x + 1 < FIELDS)								tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y));
		if (missilePos.x + 1 < FIELDS && missilePos.y + 1 < FIELDS)	tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y + 1));

		// updating ship flag
		ship->mHitTiles = 1;
		ship->mSank = true;

		// updating user's sank ships 
		mRemote->mSankShips++;

		playerAction = Net::PlayerAction::HIT_ONE;
	}
	else if (ship->get_length() > 1)
	{
		ship->mHitTiles++;

		if (!(ship->get_length() == ship->mHitTiles))
		{
			if (missilePos.x - 1 >= 0 && missilePos.y - 1 >= 0)			tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1, missilePos.y - 1));
			if (missilePos.x - 1 >= 0 && missilePos.y + 1 < FIELDS)		tiles_to_update.push_back(sf::Vector2i(missilePos.x - 1, missilePos.y + 1));
			if (missilePos.x + 1 < FIELDS && missilePos.y - 1 >= 0)		tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y - 1));
			if (missilePos.x + 1 < FIELDS && missilePos.y + 1 < FIELDS)	tiles_to_update.push_back(sf::Vector2i(missilePos.x + 1, missilePos.y + 1));

			playerAction = Net::PlayerAction::HIT_PART;
		}
		else
		{
			update_grid_after_ship_sank(*ship,missilePos);		
			ship->mSank = true;
			mRemote->mSankShips++;
			playerAction = Net::PlayerAction::HIT_AND_SANK;
		}
	}

	// updating mShotTiles with coords stored in vector
	for (auto& tile : tiles_to_update)
		mShotTiles[tile.x][tile.y] = TileStatus::MISS; // MISS means a dot is beign drawn
	std::cout << "RETURNING : ";
	Net::decode_action(playerAction);

	return playerAction;
}