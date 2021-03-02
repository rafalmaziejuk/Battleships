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

	sf::Sprite mBackgroundSprite;		// overall background sprite
	sf::Sprite mHintBackgroundSprite;	// hint background sprite 
	sf::Sprite mGridSprites[2];			// grid sprites
	sf::Sprite mGameStatus;				// sprite for game status
	sf::Vector2i mStart;				// ship start position after pressing LMB 
	sf::Vector2i mEnd;					// ship end position after pressing RMB
	bool mIsGood;						// true if clicked field is free and ship can be placed

private:
	PlayerGrid mPlayerGrid;				// player grid
	EnemyGrid mEnemyGrid;				// enemy grid
	Cursor mCursor;						// cursor
	Ship mPlayerShips[NUM_OF_SHIPS];	// player ships
	Net::Remote* mRemote;				// pointer to remote

private:
	
	/* initialization */
	
	void load_textures(void);			// loads required textures
	void init_ships(void);				// sets the lenght of the ships 
	void init_world_components(void);

	Ship* get_this_ship_head(const sf::Vector2i& cursorPos);						// returns head of clicked ship
	void add_new_ship(const sf::Event& event);
	void remove_ship(Ship* ship);

public:

	/* constructor / destructor */

	explicit World(sf::RenderWindow *window);
	~World(void);


	/* drawing and update */

	void draw(void);
	void update(void);
	void reset_game(void);
	void handle_event(const sf::Event &event, bool playerReady);
	bool all_ships_placed(void);
	void set_remote(Net::Remote* remote);
	void activate_enemy_grid(bool flag);
	void update_game_status(bool isWon);
	

	Ship* is_ship_choosen(const sf::Vector2i& cursorPos);

	PlayerGrid& get_player_grid(void);
	EnemyGrid& get_enemy_grid(void);
};