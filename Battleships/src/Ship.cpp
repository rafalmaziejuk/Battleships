#include "Ship.h"
#include "Defines.h"

Ship::Ship(void) :
	mHeadPosition(),
	mTiles(),
	mShipLength(0),
	mOrientation(Orientation::Horizontal),
	mIsAlive(false)
{

}

Ship::Ship(sf::Vector2f headPosition, uint8_t shipLength, Orientation orientation, const sf::Texture &texture) :
	mTiles(shipLength, sf::Sprite(texture)),
	mHeadPosition(headPosition),
	mShipLength(shipLength),
	mOrientation(orientation),
	mIsAlive(true)
{
	for (uint8_t i = 0; i < shipLength; i++)
		mTiles.back().setPosition(mHeadPosition.x * CELL_SIZE, mHeadPosition.y * CELL_SIZE);

	//tiles initialization
	/*sf::Vector2f shift(0.0f, 0.0f);

	for (uint8_t i = 0; i < shipLength; i++)
	{
		mTiles.push_back(sf::Sprite(texture));
		mTiles.back().setPosition((mHeadPosition.x + shift.x) * CELL_SIZE, (mHeadPosition.y + shift.y) * CELL_SIZE);

		//updating shift for the new segment position
		(mOrientation == Orientation::Horizontal) ? shift.x += 1.0f : shift.y += 1.0f;
	}*/
}

Ship::~Ship(void) 
{

}

void Ship::move_ship(void)
{

}

void Ship::draw_ship(sf::RenderWindow* window)
{
	for (auto& i : mTiles)
		window->draw(i);
}
