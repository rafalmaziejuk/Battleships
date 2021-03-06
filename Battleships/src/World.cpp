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
	init_ships();
	init_world_components();
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
	mTextures.load_resource(Textures::ID::GAMESTATUS, "assets/gamestatus.png");
}

void World::init_ships(void)
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

void World::init_world_components(void)
{
	mPlayerGrid.set_ship_texture(mTextures.get_resource(Textures::ID::SHIP_TILE));
	mPlayerGrid.set_up_ship_hint(mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_I), mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_A), mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_SANK));
	mPlayerGrid.set_dot_testure(mTextures.get_resource(Textures::ID::DOT));
	mPlayerGrid.set_sank_ship_texture(mTextures.get_resource(Textures::ID::SHIP_TILE_SANK));
	mEnemyGrid.set_ship_texture(mTextures.get_resource(Textures::ID::SHIP_TILE_SANK));
	mEnemyGrid.set_up_ship_hint(mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_I), mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_A), mTextures.get_resource(Textures::ID::HINT_SHIP_TILE_SANK));
	mEnemyGrid.set_dot_testure(mTextures.get_resource(Textures::ID::DOT));
	mEnemyGrid.set_sank_ship_texture(mTextures.get_resource(Textures::ID::SHIP_TILE_SANK));

	mHintBackgroundSprite.setTexture(mTextures.get_resource(Textures::ID::HINT_BOARD_BACKGROUND));
	mHintBackgroundSprite.setPosition(sf::Vector2f(75, 607));

	mBackgroundSprite.setTexture(mTextures.get_resource(Textures::ID::BG_GAME));
	mGridSprites[0].setTexture(mTextures.get_resource(Textures::ID::GRID));
	mGridSprites[0].setPosition(sf::Vector2f(50.0f, 50.0f));
	mGridSprites[1].setTexture(mTextures.get_resource(Textures::ID::GRID));
	mGridSprites[1].setPosition(sf::Vector2f(650.0f, 50.0f));
	mGameStatus.setTexture(mTextures.get_resource(Textures::ID::GAMESTATUS));
	mGameStatus.setPosition(375, 200);
	mCursor = Cursor(mTextures.get_resource(Textures::ID::SELECTED_TILE));
}

void World::handle_ship_adding(const sf::Event& event)
{
	if (event.mouseButton.x > 100 && event.mouseButton.y > 100 && event.mouseButton.x < 600 && event.mouseButton.y < 600)
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			mStart = mPlayerGrid.get_grid_coordinates(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			mCursor.set_cursor_mode(Cursor::Mode::DRAGGING);

			if (mPlayerGrid.is_field_free(mStart))
				mIsGood = true;
			else
				mIsGood = false;
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			mEnd = mPlayerGrid.get_grid_coordinates(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			mCursor.set_cursor_mode(Cursor::Mode::DEFAULT);

			if (mPlayerGrid.is_field_free(mEnd) && mIsGood)
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
							mPlayerGrid.update(mPlayerShips[i], ShipAction::ADD);
							break;
						}
					}
				}

				mIsGood = false;
			}
		}
	}
}

void World::handle_ship_removing(const sf::Event& event)
{
	 if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Right)
	{
		sf::Vector2f cursorPos = map_cursor_to_world(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
		Ship* clickedShip = is_ship_choosen((sf::Vector2i)cursorPos);
		if (clickedShip)
			remove_ship(clickedShip);
	}
}

void World::remove_ship(Ship* ship)
{
	mPlayerGrid.update(*ship, ShipAction::REMOVE);
}

Ship* World::get_this_ship_head(const sf::Vector2i& cursorPos)
{
	for (unsigned i = 0; i < 10; i++)
		if (mPlayerShips[i].is_on_grid() == true && mPlayerShips[i].contain_tile(cursorPos))
		{
			return &mPlayerShips[i];
		}
	return nullptr;
}

void World::draw(void)
{
	mWindow->draw(mBackgroundSprite);
	mWindow->draw(mGridSprites[0]);
	mWindow->draw(mGridSprites[1]);

	mHintBackgroundSprite.setPosition(sf::Vector2f(75, 607));
	mWindow->draw(mHintBackgroundSprite);
	mHintBackgroundSprite.setPosition(sf::Vector2f(680, 607));
	mWindow->draw(mHintBackgroundSprite);

	for (unsigned i = 0; i < NUM_OF_SHIPS; i++)
		mPlayerShips[i].draw_ship(mWindow);

	mCursor.draw(mWindow);
	mPlayerGrid.draw(mWindow);
	mEnemyGrid.draw(mWindow);

	if (mRemote->mGameOver)
		mWindow->draw(mGameStatus);
}

void World::update(void)
{
	mCursor.update(sf::Mouse::getPosition(*mWindow));
}

void World::reset_game(void)
{
	for (unsigned i = 0; i < NUM_OF_SHIPS; i++)
		mPlayerShips[i].reset();
	mPlayerGrid.reset();
	mEnemyGrid.reset();
}


void World::fire_missile(const sf::Event& event, bool playerReady)
{
	if (playerReady && mRemote->mMyTurn && !mRemote->mGameOver && mRemote->mGameStarted)
	{
		sf::Vector2i missilePos = mEnemyGrid.get_grid_coordinates(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

		if (mEnemyGrid.mShotTiles[missilePos.x][missilePos.y] == TileStatus::NUL)
		{
			mRemote->mMyTurn = false;

			// Critical section
			Net::mutex.lock();

			mRemote->mRecentlyFiredMissile = missilePos;
			mRemote->mMsgSent.ID = Net::MessageCode::MISSILE;
			mRemote->mMsgSent.coord = sf::Vector2i(missilePos);

			Net::mutex.unlock();
		}
	}
}

void World::handle_missile(sf::Vector2i coord)
{
	Ship* ship = is_ship_choosen(coord);

	if (ship == nullptr) // if pointer is nullptr then remote missed
	{
		std::cout << "Enemy missed !\n";

		mPlayerGrid.mShotTiles[coord.x][coord.y] = TileStatus::MISS;

		// setting data for feedback message
		mRemote->mMsgSent.ID = Net::MessageCode::MISS;
		mRemote->mMyTurn = true;
		activate_enemy_grid(true);
	}
	else
	{
		std::cout << "Enemy hit your ship!\n";

		mRemote->mMsgSent.ID = mPlayerGrid.update_shot_tiles(ship, coord);

		if (mRemote->mMsgSent.ID == Net::MessageCode::LOSE)
		{
			mRemote->set_up_new_party(false);
		}
		else
		{
			mRemote->mMyTurn = false;
			activate_enemy_grid(false);
		}
	}
	
	mRemote->send_message();
}

void World::handle_event(const sf::Event& event, bool playerReady)
{
	if (!playerReady)
	{
		handle_ship_adding(event);
		handle_ship_removing(event);
	}

	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (event.mouseButton.x > 700 && event.mouseButton.y > 100 && event.mouseButton.x < 1200 && event.mouseButton.y < 600)
		{
			fire_missile(event, playerReady);
		}
	}
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

void World::update_game_status(bool isWon)
{
	if (!isWon)
	{
		mGameStatus.setTextureRect(sf::IntRect(0, 0, 500, 150));
	}
	else
		mGameStatus.setTextureRect(sf::IntRect(0, 150, 500, 150));
}

Ship* World::is_ship_choosen(const sf::Vector2i& cursorPos)
{
	if (mPlayerGrid.is_field_free(cursorPos) == false)
	{
		return get_this_ship_head(cursorPos);
	}
	else
		return nullptr;
}

PlayerGrid& World::get_player_grid(void)
{
	return mPlayerGrid;
}
EnemyGrid& World::get_enemy_grid(void)
{
	return mEnemyGrid;
}
