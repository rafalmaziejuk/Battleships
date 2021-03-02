#include "Cursor.h"

#include <algorithm>

Cursor::Cursor(void) :
	mCursorSprite(),
	mCursorSprites(),
	mMode(Mode::NONE),
	mDraw(false)
{

}

Cursor::Cursor(const sf::Texture &texture) :
	mCursorSprite(texture),
	mCursorSprites(),
	mMode(Mode::NONE),
	mDraw(false)
{

}

Cursor::~Cursor(void) 
{ 

}

void Cursor::set_cursor_mode(Mode mode)
{
	if (mMode == Mode::DRAGGING && mode == Mode::DEFAULT)
		mCursorSprites.clear();

	mMode = mode;
}

void Cursor::update(sf::Vector2i mousePosition)
{
	if (((mousePosition.x > 100 && mousePosition.y > 100) && (mousePosition.x < 600 && mousePosition.y < 600) ||
		(mousePosition.x > 700 && mousePosition.y > 100) && (mousePosition.x < 1200 && mousePosition.y < 600)) && mMode != Mode::DRAGGING)
	{
		mMode = Mode::DEFAULT;
		mousePosition.x /= CELL_SIZE;
		mousePosition.y /= CELL_SIZE;

		mCursorSprite.setPosition(sf::Vector2f(float(mousePosition.x * CELL_SIZE), float(mousePosition.y * CELL_SIZE)));
	}
	else if ((mousePosition.x > 100 && mousePosition.y > 100) && (mousePosition.x < 600 && mousePosition.y < 600) &&
		mMode == Mode::DRAGGING)
	{
		mousePosition.x /= CELL_SIZE;
		mousePosition.y /= CELL_SIZE;

		sf::Vector2f position = sf::Vector2f(float(mousePosition.x * CELL_SIZE), float(mousePosition.y * CELL_SIZE));

		for (auto &sprite : mCursorSprites)
		{
			if (sprite.getPosition() == position)
				return;
		}

		sf::Sprite sprite;
		sprite.setTexture(*mCursorSprite.getTexture());
		sprite.setPosition(position);

		mCursorSprites.push_back(sprite);
	}
	else
		mMode = Mode::NONE;
}

void Cursor::draw(sf::RenderWindow *window) const
{
	if (mMode == Mode::DEFAULT)
		window->draw(mCursorSprite);
	else if (mMode == Mode::DRAGGING)
	{
		for (auto &sprite : mCursorSprites)
			window->draw(sprite);
	}
}