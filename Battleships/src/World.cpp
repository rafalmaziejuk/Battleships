#include "World.h"
#include <iostream>

World::World(sf::RenderWindow *window) :
	mWindow(window),
	mTextures(),
	mShips(),
	mShipPicked(false),
	mActuallyPickedShip(nullptr)
{
	load_textures();
	mBackground.setTexture(mTextures.get_resource(Textures::ID::GAME_BACKGROUND));

	mShipsGrid = new Grid(sf::Vector2i(50, 50), mTextures);
	mTargetsGrid = new Grid(sf::Vector2i(650, 50), mTextures);
	mCursor = Cursor(mTextures.get_resource(Textures::ID::SELECTED_TILE));


	// grid fields allocation

	mUnavailableFields = new bool* [FIELDS];

	for (unsigned i = 0; i < FIELDS; i++)
	{
		mUnavailableFields[i] = new bool[FIELDS];
		for (unsigned j = 0; j < FIELDS; j++)
		{
			mUnavailableFields[i][j] = false;
		}
	}

	init_ships();
}

World::~World(void)
{
	delete mShipsGrid;
	delete mTargetsGrid;
	for (unsigned i = 0; i < FIELDS; i++)
	{
		delete mUnavailableFields[i];
	}
	delete mUnavailableFields;

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
	mShips.push_back(Ship(0,sf::Vector2f(0.0f,5.0f), 3, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(1,sf::Vector2f(2.0f,1.0f), 4, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE), mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(2,sf::Vector2f(2.0f,8.0f), 2, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE), mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(3,sf::Vector2f(4.0f,2.0f), 2, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE), mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(4,sf::Vector2f(4.0f,9.0f), 3, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(5,sf::Vector2f(8.0f,0.0f), 2, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(6,sf::Vector2f(7.0f,3.0f), 1, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(7,sf::Vector2f(9.0f,3.0f), 1, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(8,sf::Vector2f(7.0f,5.0f), 1, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields(), mUnavailableFields));
	mShips.push_back(Ship(9,sf::Vector2f(9.0f,5.0f), 1, Orientation::Vertical, mTextures.get_resource(Textures::ID::SHIP_TILE),mShipsGrid->get_grid_fields(), mUnavailableFields));
}

bool World::clicked_on_ships_grid(const sf::Vector2f position)
{
	if (position.x - 2 >= 0 && position.x - 2 < FIELDS && position.y - 2 >= 0 && position.y - 2 < FIELDS)
		return true;
	else return false;
}

Ship* World::is_ship_choosen(const sf::Vector2i& cursorPos)
{
	bool** shipGrid = mShipsGrid->get_grid_fields();
	if (shipGrid[cursorPos.x][cursorPos.y] == true)
	{
		//std::cout << "TRUE";
		return get_this_ship_head(cursorPos);
	}
	else
		return nullptr;
}

Ship* World::get_this_ship_head(const sf::Vector2i& cursorPos)
{
	for (auto& i : mShips)
		if (i.contain_tile(cursorPos))
			return &i;
	return nullptr;
}

void World::draw(void) const
{
	mWindow->draw(mBackground);

	mShipsGrid->draw(mWindow,true, mUnavailableFields);
	mTargetsGrid->draw(mWindow,false,nullptr);

	for (auto i : mShips)
		i.draw_ship(mWindow);
	mCursor.draw(mWindow);
}

void World::update(void)
{
	mCursor.update(sf::Mouse::getPosition(*mWindow));
	
	if(mShipPicked)
	{
		//std::cout << "wtf";
		//std::cout << mMousePositionWindow.x << " " << mMousePositionWindow.y << "\n";
		mActuallyPickedShip->set_position(mMousePositionWindow);
	}
}

void World::handle_input(sf::Vector2i mousePosition, const sf::Event& event)
{
	mMousePositionWindow = mousePosition;

	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	if (event.type == sf::Event::MouseButtonPressed)
	{

		sf::Vector2f cursorPosition(mousePosition.x / CELL_SIZE, mousePosition.y / CELL_SIZE);
		if (clicked_on_ships_grid(cursorPosition))
		{
			//std::cout << position.y-2<<" "<<position.x-2<<"\n\n";

			mActuallyPickedShip = is_ship_choosen(sf::Vector2i(cursorPosition.y - 2, cursorPosition.x - 2));
			if (mActuallyPickedShip != nullptr)
			{
				std::cout << "\n\n\n" << "CLICK ON SHIP";
				mShipPicked = true;

			}
		}
		//Ship* ship;
		//mShips.push_back(Ship(position, 1, Orientation::Horizontal, mTextures.get_resource(Textures::ID::SHIP_TILE)));
	}
	else if (event.type == sf::Event::MouseButtonReleased)
		mShipPicked = false;
}