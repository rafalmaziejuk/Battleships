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

// GameState world, contains Grids and all essential components like Ships, sprites etc..
class World : sf::NonCopyable
{
private:
	enum { NUM_OF_SHIPS = 10 };

private:
	sf::RenderWindow *mWindow;
	TextureManager mTextures;

	sf::Sprite mBackgroundSprite;		// background sprite
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
	void init_world_components(void);	// world components like sprites,grids.. initialization 
	
	/* utility functions */
	void handle_ship_adding(const sf::Event& event);				// handles mouse button event and adds a new ship depending on current circumstances
	void handle_ship_removing(const sf::Event& event);				// handles mouse button event and removes ship if pressed one
	void remove_ship(Ship* ship);									// removes ship from the player grid
	void fire_missile(const sf::Event& event, bool playerReady);	// checks if missile can be fired, if yes - writes data to a msg buffer, the second thread will send it to the remote
	Ship* get_this_ship_head(const sf::Vector2i& cursorPos);		// returns head of clicked ship

public:

	/* constructor / destructor */

	explicit World(sf::RenderWindow *window);
	~World(void);

	/* drawing and update */
	void draw(void);		
	void update(void);
	void reset_game(void);

	/* utility functions */
	void handle_event(const sf::Event &event, bool playerReady);	// handles sfml event in world 
	bool all_ships_placed(void);									// true if user placed all 10 ships on the grid, false otherwise
	void set_remote(Net::Remote* remote);							// sets remote pointer to Client or Host
	void activate_enemy_grid(bool flag);							// activated or deactivates enemy grid by setting different textures
	void update_game_status(bool isWon);							// sets different texture rect depending on game status (won or lose)
	Ship* is_ship_choosen(const sf::Vector2i& cursorPos);			// return pointer to the ship if it contains given tile
	PlayerGrid& get_player_grid(void);								// returns reference to player grid
	EnemyGrid& get_enemy_grid(void);								// returns reference to enemy grid
};