#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"
#include "ResourceIdentifiers.h"
#include "Grid.h"

class World : sf::NonCopyable
{
private:
	sf::RenderWindow *mWindow;
	TextureManager mTextures;
	sf::Sprite mBackground;

private:
	void load_textures(void);

private:
	Grid *mShipsGrid;
	Grid *mTargetsGrid;

public:
	explicit World(sf::RenderWindow *window);
	~World(void);

	void draw(void);
	void update(void);
};