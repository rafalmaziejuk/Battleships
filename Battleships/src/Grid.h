#pragma once

#include <SFML/Graphics.hpp>

#include "ResourceIdentifiers.h"
#include "Ship.h"

class Grid
{
private:
	static const int CELL_SIZE = 50;
	static const int FIELDS = 10;
	static const int GRID_SIZE = CELL_SIZE * (FIELDS + 1);

private:
	sf::Vector2i mGridOrigin;
	sf::Sprite mGridSprite;

private:
	bool mGridFields[FIELDS][FIELDS] = { false };
	std::vector<Ship> mShips;

	struct Cursor
	{
		sf::Sprite mCursorSprite;
		bool mDraw = false;

		explicit Cursor(const sf::Texture &texture) : mCursorSprite(texture) { }
		~Cursor(void) { }

		void set_position(sf::Vector2f position)
		{
			mCursorSprite.setPosition(sf::Vector2f(position.x * CELL_SIZE, position.y * CELL_SIZE));
		}
	} mCursor;

public:
	Grid(sf::Vector2i &gridOrigin, const TextureManager &textures);
	~Grid(void);

	void draw(sf::RenderWindow *window) const;
	void update_cursor(sf::Vector2i mousePosition);
};