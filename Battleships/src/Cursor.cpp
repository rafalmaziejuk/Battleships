#include "Cursor.h"

Cursor::Cursor(void) : 
	mCursorSprite() 
{

}

Cursor::Cursor(const sf::Texture &texture) : 
	mCursorSprite(texture) 
{

}

Cursor::~Cursor(void) 
{ 

}

void Cursor::update(sf::Vector2i mousePosition)
{
	if ((mousePosition.x > 100 && mousePosition.y > 100) && (mousePosition.x < 600 && mousePosition.y < 600) ||
		(mousePosition.x > 700 && mousePosition.y > 100) && (mousePosition.x < 1200 && mousePosition.y < 600))
	{
		mousePosition.x /= CELL_SIZE;
		mousePosition.y /= CELL_SIZE;

		mCursorSprite.setPosition(sf::Vector2f(mousePosition.x * CELL_SIZE, mousePosition.y * CELL_SIZE));
		mDraw = true;
	}
	else
		mDraw = false;
}

void Cursor::draw(sf::RenderWindow *window) const
{
	if (mDraw == true)
		window->draw(mCursorSprite);
}