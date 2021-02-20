#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class Orientation
{
	Horizontal, Vertical
};
/*

to do :

	fix texture, it shouldnt be allocated every time creating new ship

*/


class Ship
{
private:
	static const int CELL_SIZE = 50;
	static const int FIELDS = 10;
	static const int GRID_SIZE = CELL_SIZE * (FIELDS + 1);
	
	
	sf::Texture* mShipTileTexture;
	sf::Vector2f mHeadPosition;
	sf::Sprite temp;
	std::vector<sf::Sprite> mTiles;

	uint8_t mShipLenght;
	Orientation mOrientation;
	bool mIsAlive;

	void init_ship(void);

public:
	Ship(sf::Vector2f headPosition, uint8_t shipLenght, Orientation orientation, sf::Texture* shipTexture);
	~Ship();


	void move_ship(void);
	void draw_ship(sf::RenderWindow* window);


};

