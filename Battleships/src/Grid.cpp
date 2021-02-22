#include "Grid.h"
#include "ResourceManager.h"
#include <iostream>
#include <windows.h>

/////////////////////////////////////////////////////////////////
// for debugging purpose only
inline static void cls(void)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD());
}

inline static void console_cursor(bool flag)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = flag; 
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/////////////////////////////////////////////////////////////////

Grid::Grid(void) :
	mGridOrigin(),
	mGridSprite()
{

}

Grid::Grid(sf::Vector2i &gridOrigin, const TextureManager &textures) :
	mGridOrigin(gridOrigin),
	mGridSprite(textures.get_resource(Textures::ID::GRID))
{
	mGridSprite.setPosition(float(gridOrigin.x), float(gridOrigin.y));

	// grid fields allocation
	mGridFields = new bool* [FIELDS];
	mUnavailableFields = new bool* [FIELDS];

	for (unsigned i = 0; i < FIELDS; i++)
	{
		mGridFields[i] = new bool[FIELDS];
		mUnavailableFields[i] = new bool [FIELDS];
		for (unsigned j = 0; j < FIELDS; j++)
		{
			mGridFields[i][j] = false;
			mUnavailableFields[i][j] = false;
		}
	}
}

Grid::~Grid(void)
{
	for (unsigned i = 0; i < FIELDS; i++)
	{
		delete mGridFields[i];
		delete mUnavailableFields[i];
	}
	delete mGridFields;
	delete mUnavailableFields;

}

void Grid::draw(sf::RenderWindow *window, bool consoleDebug) const
{
	window->draw(mGridSprite);


	if (consoleDebug)
	{
		// for debugging purpose only
		//////////////////////////////////////////////////
		
		console_cursor(false);
		std::cout << "GridFields\n";
		std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
		for (unsigned i = 0; i < FIELDS; i++)
		{
			std::cout << i << " ";
			for (unsigned j = 0; j < FIELDS; j++)
			{
				(mGridFields[i][j] == false) ? std::cout << ". " : std::cout << "x ";
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
		std::cout << "UnavaliableFields\n";
		std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
		for (unsigned i = 0; i < FIELDS; i++)
		{
			std::cout << i << " ";
			for (unsigned j = 0; j < FIELDS; j++)
			{
				(mUnavailableFields[i][j] == false) ? std::cout << ". " : std::cout << "x ";
			}
			std::cout << "\n";
		}
		cls();
		
		//////////////////////////////////////////////////
	}
}

bool** Grid::get_grid_fields(void)
{
	return mGridFields;
}

bool** Grid::get_unavailable_fields()
{
	return mUnavailableFields;
}