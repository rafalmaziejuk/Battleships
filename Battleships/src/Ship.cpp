#include "Ship.h"

Ship::Ship(sf::Vector2f headPosition, uint8_t shipLenght, Orientation orientation, sf::Texture* shipTexture) 
{
	mShipLenght = shipLenght;
	mOrientation = orientation;
	mHeadPosition = headPosition;
	mShipTileTexture = shipTexture;
	init_ship();

}

Ship::~Ship() 
{

}

void Ship::init_ship(void)
{
	
	bool mIsAlive = true;

	//tiles initialization
	sf::Vector2f shift(0.0f,0.0f);

	//temp.setTexture(*mShipTileTexture);

	for (uint8_t i = 0; i < mShipLenght; i++)
	{
		mTiles.push_back(sf::Sprite());
		mTiles.back().setPosition((mHeadPosition.x+shift.x) * CELL_SIZE, (mHeadPosition.y+shift.y) * CELL_SIZE);
		mTiles.back().setTexture(*mShipTileTexture);

		//updating shift for the new segment position
		(mOrientation == Orientation::Horizontal) ? shift.x += 1.0f : shift.y += 1.0f;
	}
	
}

void Ship::move_ship(void)
{

}

void Ship::draw_ship(sf::RenderWindow* window)
{
	
	for (auto& i : mTiles)
		window->draw(i);
}
