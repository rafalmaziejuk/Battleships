#include "World.h"

World::World(sf::RenderWindow *window) :
	mWindow(window),
	mTextures(),
	mShips()
{
	load_textures();
	mBackground.setTexture(mTextures.get_resource(Textures::ID::GAME_BACKGROUND));

	mShipsGrid = new Grid(sf::Vector2i(50, 50), mTextures);
	mTargetsGrid = new Grid(sf::Vector2i(650, 50), mTextures);
	mCursor = Cursor(mTextures.get_resource(Textures::ID::SELECTED_TILE));

	init_ships();
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

void World::init_ships(void)
{
	mShips.push_back(Ship(sf::Vector2f(5.0f,0.0f), 3, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(1.0f,2.0f), 4, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE), mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(8.0f,2.0f), 2, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE), mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(2.0f,4.0f), 2, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE), mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(9.0f,4.0f), 3, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(0.0f,8.0f), 2, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(3.0f,7.0f), 1, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(3.0f,9.0f), 1, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(5.0f,7.0f), 1, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields()));
	mShips.push_back(Ship(sf::Vector2f(5.0f,9.0f), 1, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields()));

}

void World::draw(void) const
{
	mWindow->draw(mBackground);

	mShipsGrid->draw(mWindow,true);
	mTargetsGrid->draw(mWindow,false);

	for (auto i : mShips)
		i.draw_ship(mWindow);
	mCursor.draw(mWindow);
}

void World::update(void)
{
	mCursor.update(sf::Mouse::getPosition(*mWindow));
}

void World::handle_input(sf::Vector2i mousePosition, bool isPressed)
{
	if (isPressed == true)
	{
		/*
		sf::Vector2f position(mousePosition.x / CELL_SIZE, mousePosition.y / CELL_SIZE);
		mShips.push_back(Ship(position, 1, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE)));
		*/
	}
}