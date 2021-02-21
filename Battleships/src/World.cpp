#include "World.h"

World::World(sf::RenderWindow *window) :
	mWindow(window),
	mTextures(),
	mShips()
{
	load_textures();
	mBackground.setTexture(mTextures.get_resource(Textures::ID::GAME_BACKGROUND));

	mShipsGrid = Grid(sf::Vector2i(50, 50), mTextures);
	mTargetsGrid = Grid(sf::Vector2i(650, 50), mTextures);
	mCursor = Cursor(mTextures.get_resource(Textures::ID::SELECTED_TILE));
}

World::~World(void)
{
	
}

void World::load_textures(void)
{
	mTextures.load_resource(Textures::ID::GAME_BACKGROUND, "assets/gamebg.png");
	mTextures.load_resource(Textures::ID::GRID, "assets/grid.png");
	mTextures.load_resource(Textures::ID::SELECTED_TILE, "assets/selectedtile.png");
	mTextures.load_resource(Textures::ID::SHIP_TILE, "assets/shiptile.png");
}

void World::draw(void) const
{
	mWindow->draw(mBackground);
	mCursor.draw(mWindow);
	mShipsGrid.draw(mWindow);
	mTargetsGrid.draw(mWindow);

	for (auto i : mShips)
		i.draw_ship(mWindow);
}

void World::update(void)
{
	mCursor.update(sf::Mouse::getPosition(*mWindow));
}

void World::handle_input(sf::Vector2i mousePosition, bool isPressed)
{
	if (isPressed == true)
	{
		sf::Vector2f position(mousePosition.x / CELL_SIZE, mousePosition.y / CELL_SIZE);
		mShips.push_back(Ship(position, 1, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE)));
	}
}