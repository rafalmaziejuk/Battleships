#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

class Cursor
{
private:
	enum { CELL_SIZE = 50 };

public:
	enum class Mode : uint8_t
	{
		NONE,
		DEFAULT,
		DRAGGING
	};

private:
	sf::Sprite mCursorSprite;
	std::vector<sf::Sprite> mCursorSprites;

private:
	Mode mMode;
	bool mDraw;

public:
	Cursor(void);
	explicit Cursor(const sf::Texture &texture);
	~Cursor(void);

	void set_cursor_mode(Mode mode);

	void update(sf::Vector2i mousePosition);
	void draw(sf::RenderWindow *window) const;
};