#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Cursor
{
private:
	enum { CELL_SIZE = 50 };
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