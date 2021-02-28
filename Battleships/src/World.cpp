#include "World.h"
#include <iostream>

static sf::Vector2f map_cursor_to_world(const sf::Vector2i mousePos)
{
	return sf::Vector2f((mousePos.x / 50.0f)-2, (mousePos.y / 50.0f)-2);
}

World::World(sf::RenderWindow* window) :
	mWindow(window),
	mTextures(),
	mIsGood(false),
	mPlayerGrid(PlayerGrid(sf::Vector2i(100, 100))),
	mEnemyGrid(EnemyGrid(sf::Vector2i(700, 100))),
	mRemote(nullptr)

{
	load_textures();
	set_ships();

	mPlayerGrid.set_ship_texture(mTextures.get_resource(Textures::ID::SHIP_TILE));
	mPlayerGrid.set_hint_ship_texture(mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_I), mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_A));
	mPlayerGrid.set_dot_testure(mTextures.get_resource(Textures::ID::DOT));
	mEnemyGrid.set_ship_texture(mTextures.get_resource(Textures::ID::SHIP_TILE_SANK));
	mEnemyGrid.set_hint_ship_texture(mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_A), mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_SANK));
	mEnemyGrid.set_dot_testure(mTextures.get_resource(Textures::ID::DOT));

	mHintBackgroundSprite.setTexture(mTextures.get_resource(Textures::ID::HINT_BOARD_BACKGROUND));
	mHintBackgroundSprite.setPosition(sf::Vector2f(75, 607));
	
	mBackgroundSprite.setTexture(mTextures.get_resource(Textures::ID::BG_GAME));
	mGridSprites[0].setTexture(mTextures.get_resource(Textures::ID::GRID));
	mGridSprites[0].setPosition(sf::Vector2f(50.0f, 50.0f));
	mGridSprites[1].setTexture(mTextures.get_resource(Textures::ID::GRID));
	mGridSprites[1].setPosition(sf::Vector2f(650.0f, 50.0f));
	
	mCursor = Cursor(mTextures.get_resource(Textures::ID::SELECTED_TILE));
}

World::~World(void)
{

}

void World::load_textures(void)
{
	mTextures.load_resource(Textures::ID::BG_GAME, "assets/gamebg.png");
	mTextures.load_resource(Textures::ID::GRID, "assets/grid.png");
	mTextures.load_resource(Textures::ID::GRIDINNACTIVE, "assets/gridinnactive.png");
	mTextures.load_resource(Textures::ID::SELECTED_TILE, "assets/selectedtile.png");
	mTextures.load_resource(Textures::ID::SHIP_TILE, "assets/shiptile.png");
	mTextures.load_resource(Textures::ID::HINT_SHIP_TILE_A, "assets/hinttile.png");
	mTextures.load_resource(Textures::ID::HINT_SHIP_TILE_I, "assets/innactivehinttile.png");
	mTextures.load_resource(Textures::ID::HINT_BOARD_BACKGROUND, "assets/hintbackground.png");
	mTextures.load_resource(Textures::ID::DOT, "assets/dot.png");
	mTextures.load_resource(Textures::ID::HINT_SHIP_TILE_SANK, "assets/sankhinttile.png");
	mTextures.load_resource(Textures::ID::SHIP_TILE_SANK, "assets/sankshiptile.png");

}


void World::set_ships(void)
{
	mPlayerShips[0].set_length(1);
	mPlayerShips[1].set_length(1);
	mPlayerShips[2].set_length(1);
	mPlayerShips[3].set_length(1);
	mPlayerShips[4].set_length(2);
	mPlayerShips[5].set_length(2);
	mPlayerShips[6].set_length(2);
	mPlayerShips[7].set_length(3);
	mPlayerShips[8].set_length(3);
	mPlayerShips[9].set_length(4);
}

void World::draw(void)
{
	mWindow->draw(mBackgroundSprite);
	mWindow->draw(mGridSprites[0]);
	mWindow->draw(mGridSprites[1]);
	mWindow->draw(mHintBackgroundSprite);

	mPlayerGrid.draw(mWindow);
	mEnemyGrid.draw(mWindow);
	for (unsigned i = 0; i < NUM_OF_SHIPS; i++)
		mPlayerShips[i].draw_ship(mWindow);
	mCursor.draw(mWindow);
}

void World::update(void)
{
	mCursor.update(sf::Mouse::getPosition(*mWindow));

}

void World::handle_input(const sf::Event::MouseButtonEvent &mouse, bool isPressed, bool playerReady)
{
	//left button
	if (mouse.button == sf::Mouse::Left)
	{

		if (mouse.x > 100 && mouse.y > 100 && mouse.x < 600 && mouse.y < 600)
		{
			if(!playerReady)
				add_new_ship(mouse, isPressed);
		}
		else if (mouse.x > 700 && mouse.y > 100 && mouse.x < 1200 && mouse.y < 600)
		{
			if (playerReady && mRemote->mMyTurn)
			{
				sf::Vector2i missilePos = mEnemyGrid.get_grid_coordinates(sf::Vector2i(mouse.x, mouse.y));
				mEnemyGrid.fire_missile(missilePos);
				mRemote->mMyTurn = false;
				activate_enemy_grid(false);

				// Critical section
				Net::mutex.lock();

				mRemote->mRecentlyFiredMissile = missilePos;
				mRemote->mMsgSent.ID = Net::PlayerAction::MISSILE;
				mRemote->mMsgSent.coord = sf::Vector2i(missilePos);

				Net::mutex.unlock();
			}
		}
	}
	else if (mouse.button == sf::Mouse::Right)
	{
		if (isPressed && !playerReady)
		{
			sf::Vector2f cursorPos = map_cursor_to_world(sf::Vector2i(mouse.x, mouse.y));
			Ship* clickedShip = is_ship_choosen((sf::Vector2i)cursorPos);
			if (clickedShip)
				remove_ship(clickedShip);
		}
	}
}

void World::add_new_ship(const sf::Event::MouseButtonEvent& mouse, bool isPressed)
{
	if (isPressed == true)
	{
		mStart = mPlayerGrid.get_grid_coordinates(sf::Vector2i(mouse.x, mouse.y));

		if (mPlayerGrid.is_field_free(mStart) == true)
			mIsGood = true;
		else
			mIsGood = false;
	}

	if (isPressed == false)
	{
		mEnd = mPlayerGrid.get_grid_coordinates(sf::Vector2i(mouse.x, mouse.y));

		if (mPlayerGrid.is_field_free(mEnd) == true && mIsGood == true)
		{
			uint8_t length = 1;

			if (mEnd.x == mStart.x)
				length += abs(mEnd.y - mStart.y);
			else if (mEnd.y == mStart.y)
				length += abs(mEnd.x - mStart.x);
			else
			{
				mIsGood = false;
				return;
			}

			if (length <= 4)
			{
				for (int i = 0; i < NUM_OF_SHIPS; i++)
				{
					if (mPlayerShips[i].get_length() == length && mPlayerShips[i].is_on_grid() == false)
					{
						mPlayerShips[i].set_position(mStart, mEnd);
						mPlayerGrid.update(mPlayerShips[i],ShipAction::ADD);
						break;
					}
				}
			}

			mIsGood = false;
		}
	}
}

void World::remove_ship(Ship* ship)
{
	//std::cout << "Usuwamy\n";
	mPlayerGrid.update(*ship, ShipAction::REMOVE);
}

Ship* World::is_ship_choosen(const sf::Vector2i& cursorPos)
{
	//bool** shipGrid = mPlayerGrid->get_grid_fields();
	if (mPlayerGrid.is_field_free(cursorPos) == false)
	{
		//std::cout << "TRUE";
		return get_this_ship_head(cursorPos);
	}
	else
		return nullptr;
}

Ship* World::get_this_ship_head(const sf::Vector2i& cursorPos)
{
	for (unsigned i = 0 ; i < 10 ; i++ )
		if (mPlayerShips[i].is_on_grid() == true && mPlayerShips[i].contain_tile(cursorPos))
		{
			return &mPlayerShips[i];
			//std::cout << "mam";
		}
	return nullptr;

}

bool World::all_ships_placed(void)
{
	return (mPlayerGrid.mPlacedShips == 10) ? true : false;
}

void World::set_remote(Net::Remote* remote)
{
	mRemote = remote;
	mPlayerGrid.set_remote(remote);
	mEnemyGrid.set_remote(remote);
	activate_enemy_grid(false);
}

void  World::activate_enemy_grid(bool flag)
{
	if (flag)
		std::cout << "AKTYWUJE GRID\n";
	if (mRemote != nullptr)
	{
		(mRemote->mMyTurn) ? mGridSprites[1].setTexture(mTextures.get_resource(Textures::ID::GRID))
			: mGridSprites[1].setTexture(mTextures.get_resource(Textures::ID::GRIDINNACTIVE));

	}
}

PlayerGrid& World::get_player_grid(void)
{
	return mPlayerGrid;
}
EnemyGrid& World::get_enemy_grid(void)
{
	return mEnemyGrid;
}
