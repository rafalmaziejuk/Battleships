#pragma once

#include <SFML/Graphics.hpp>

#include "Defines.h"

class Cursor
{
private:
	sf::Sprite mCursorSprite;

private:
	bool mDraw = false;

public:
	Cursor(void);
	explicit Cursor(const sf::Texture &texture);
	~Cursor(void);

	void update(sf::Vector2i mousePosition);
	void draw(sf::RenderWindow *window) const;
};