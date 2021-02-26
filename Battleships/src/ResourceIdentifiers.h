#pragma once

#include <cstdint>

namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum class ID : uint8_t
	{
		MENU_BACKGROUND,
		MENUBUTTON1,
		MENUBUTTON2,
		MENUBUTTON3,
		CONNECTBUTTON1,
		GAME_BACKGROUND,
		CONNECT_SCREEN,
		GRID,
		SELECTED_TILE,
		SHIP_TILE,
		HINT_SHIP_TILE_A,
		HINT_SHIP_TILE_I,
		HINT_BOARD_BACKGROUND,
		BACKBUTTON,
		CONNECT_STATUS,
		CANCELBUTTON
	};
}

namespace Fonts
{
	enum class ID : uint8_t
	{
		SANSATION,
		ANIRB,
		ANIRM,
		ANONYMOUS_PRO,
		VIKING
	};
}

template <typename Type, typename ID>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;
typedef ResourceManager<sf::Font, Fonts::ID> FontManager;