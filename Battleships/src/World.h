#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"
#include "ResourceIdentifiers.h"
#include "Defines.h"
#include "Grid.h"
#include "Cursor.h"
#include "Ship.h"

class World : sf::NonCopyable
{
private:
	sf::RenderWindow *mWindow;
	TextureManager mTextures;
	sf::Sprite mBackgroundSprite;
	sf::Sprite mGridSprites[2];
	sf::Vector2i mStart;
	sf::Vector2i mEnd;

private:

	Grid mPlayerGrid;
	Grid mEnemyGrid;
	Cursor mCursor;
	Ship mPlayerShips[NUM_OF_SHIPS];

private:
	void load_textures(void);
	void set_ships(void);

public:
	explicit World(sf::RenderWindow *window);
	~World(void);

	void draw(void) const;
	void update(void);

	void handle_input(const sf::Event::MouseButtonEvent &mouse, bool isPressed);

};