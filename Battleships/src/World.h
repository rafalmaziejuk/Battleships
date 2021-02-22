#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceManager.h"
#include "ResourceIdentifiers.h"
#include "Defines.h"
#include "Grid.h"
#include "Cursor.h"
#include "Ship.h"

class World : sf::NonCopyable
{
private:
	sf::RenderWindow *mWindow;
	TextureManager mTextures;
	sf::Sprite mBackground;

private:
	void load_textures(void);
	void init_ships(void);
	bool clicked_on_ships_grid(const sf::Vector2f position);
	Ship* is_ship_choosen(const sf::Vector2i& cursorPos);
	Ship* get_this_ship_head(const sf::Vector2i& cursorPos);

private:
	Grid* mShipsGrid;
	Grid* mTargetsGrid;
	Cursor mCursor;
	std::vector<Ship> mShips;
	bool** mUnavailableFields;
	bool mShipPicked;
	Ship* mActuallyPickedShip;
	sf::Vector2i mMousePositionWindow;

public:
	explicit World(sf::RenderWindow *window);
	~World(void);

	void draw(void) const;
	void update(void);
	void handle_input(sf::Vector2i mousePosition, const sf::Event& event);
};