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
	sf::Sprite mBackground;

private:
	void load_textures(void);
	void init_ships(void);

private:
	Grid* mShipsGrid;
	Grid* mTargetsGrid;
	Cursor mCursor;
	std::vector<Ship> mShips;

public:
	explicit World(sf::RenderWindow *window);
	~World(void);

	void draw(void) const;
	void update(void);
	void handle_input(sf::Vector2i mousePosition, bool isPressed);
};