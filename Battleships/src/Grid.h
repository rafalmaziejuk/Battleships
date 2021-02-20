#pragma once

#include <SFML/Graphics.hpp>

class Grid : sf::Sprite
{
private:
	static const int CELL_SIZE = 50;
	static const int FIELDS = 10;
	static const int GRID_SIZE = CELL_SIZE * (FIELDS + 1);

private:
	bool mGridFields[FIELDS][FIELDS] = { false };

	sf::Vector2i mGridOrigin;
	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::RectangleShape mCursor;

public:
	Grid(sf::Vector2i &&gridOrigin);
	~Grid(void);

	void draw(sf::RenderWindow *window) const;
	void set_cursor_position(sf::Vector2f mousePosition);
};