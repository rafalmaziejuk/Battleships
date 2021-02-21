#include "Grid.h"
#include "ResourceManager.h"

Grid::Grid(void) :
	mGridOrigin(),
	mGridSprite()
{

}

Grid::Grid(sf::Vector2i &gridOrigin, const TextureManager &textures) :
	mGridOrigin(gridOrigin),
	mGridSprite(textures.get_resource(Textures::ID::GRID))
{
	mGridSprite.setPosition(gridOrigin.x, gridOrigin.y);
}

Grid::~Grid(void)
{

}

void Grid::draw(sf::RenderWindow *window) const
{
	window->draw(mGridSprite);
}