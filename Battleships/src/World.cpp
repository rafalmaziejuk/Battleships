#include "World.h"

World::World(sf::RenderWindow *window) :
	mWindow(window),
	mTextures()
{
	load_textures();
	mBackground.setTexture(mTextures.get_resource(Textures::ID::GAME_BACKGROUND));

	mShipsGrid = new Grid(sf::Vector2i(50, 50), mTextures);
	mTargetsGrid = new Grid(sf::Vector2i(650, 50), mTextures);
}

World::~World(void)
{
	delete mShipsGrid;
	delete mTargetsGrid;
}

void World::load_textures(void)
{
	mTextures.load_resource(Textures::ID::GAME_BACKGROUND, "assets/gamebg.png");
	mTextures.load_resource(Textures::ID::GRID, "assets/grid.png");
	mTextures.load_resource(Textures::ID::SELECTED_TILE, "assets/selectedtile.png");
	mTextures.load_resource(Textures::ID::SHIP_TILE, "assets/shiptile.png");
}

void World::draw(void)
{
	mWindow->draw(mBackground);
	mShipsGrid->draw(mWindow);
	mTargetsGrid->draw(mWindow);
}

void World::update(void)
{
	mShipsGrid->update_cursor(sf::Mouse::getPosition(*mWindow));
	mTargetsGrid->update_cursor(sf::Mouse::getPosition(*mWindow));
}