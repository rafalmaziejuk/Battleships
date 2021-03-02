#pragma once

#include "ResourceManager.h"
#include "ResourceIdentifiers.h"
#include "PlayerGrid.h"
#include "EnemyGrid.h"
#include "Cursor.h"
#include "Ship.h"
#include "Remote.h"


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Texture.hpp>


class World : sf::NonCopyable
{
private:
	enum { NUM_OF_SHIPS = 10 };

private:
	sf::RenderWindow *mWindow;
	TextureManager mTextures;
	sf::Sprite mBackgroundSprite;
	sf::Sprite mHintBackgroundSprite;
	sf::Sprite mGridSprites[2];
	sf::Sprite mGameStatus;
	sf::Vector2i mStart;
	sf::Vector2i mEnd;
	bool mIsGood;

private:
	PlayerGrid mPlayerGrid;
	EnemyGrid mEnemyGrid;
	Cursor mCursor;
	Ship mPlayerShips[NUM_OF_SHIPS];
	Net::Remote* mRemote;
private:
	
	void load_textures(void);
	void set_ships(void);
	
	Ship* get_this_ship_head(const sf::Vector2i& cursorPos);
	void add_new_ship(const sf::Event::MouseButtonEvent& mouse, bool isPressed);
	void remove_ship(Ship* ship);

public:
	explicit World(sf::RenderWindow *window);
	~World(void);

	void draw(void);
	void update(void);
	void handle_input(const sf::Event::MouseButtonEvent &mouse, bool isPressed, bool playerReady);
	bool all_ships_placed(void);
	void set_remote(Net::Remote* remote);
	void activate_enemy_grid(bool flag);
	void update_game_status(bool isWon);
	void reset_game(void);

	Ship* is_ship_choosen(const sf::Vector2i& cursorPos);

	PlayerGrid& get_player_grid(void);
	EnemyGrid& get_enemy_grid(void);

};