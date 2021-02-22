#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.h"
#include "Defines.h"

class Grid
{
private:
	sf::Vector2i mGridOrigin;
	sf::Sprite mGridSprite;

private:
	bool** mGridFields;
	

public:
	Grid(void);
	Grid(sf::Vector2i &gridOrigin, const TextureManager &textures);
	~Grid(void);

	void draw(sf::RenderWindow *window, bool consoleDebug) const;
	bool** get_grid_fields(void);
	
};