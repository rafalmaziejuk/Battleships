#pragma once

#include <SFML/Graphics.hpp>

#include "Ship.h"

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
	sf::Texture mShipTileTexture;
	sf::Sprite mSprite;
	std::vector<Ship> mShips;


	struct Cursor
	{
		sf::RectangleShape mShape;
		sf::Texture mCursorTex;
		bool mDraw = false;

		Cursor(void) :
			mShape()
		{
			mCursorTex.loadFromFile("assets/selectedtile.png");
			mShape.setTexture(&mCursorTex);
			//mShape.setFillColor(sf::Color::Cyan);
			mShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
		}
		~Cursor(void) { }

		void setPosition(sf::Vector2f position)
		{
			mShape.setPosition(sf::Vector2f(position.x * CELL_SIZE, position.y * CELL_SIZE));
		}
	} mCursor;

public:
	Grid(sf::Vector2i &&gridOrigin);
	~Grid(void);

	void draw(sf::RenderWindow *window) const;
	void update_cursor(sf::Vector2i mousePosition);
};