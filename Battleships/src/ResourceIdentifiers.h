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
		BG_MENU,
		BG_GAME,
		B_MENU1,
		B_MENU2,
		B_MENU3,
		B_BACK,
		B_CONNECT,
		B_CANCEL,
		B_READY,
		CONNECT_SCREEN,
		GRID,
		SELECTED_TILE,
		SHIP_TILE,
		HINT_SHIP_TILE_A,
		HINT_SHIP_TILE_I,
		HINT_BOARD_BACKGROUND,
		CONNECT_STATUS,
		DOT,
		HINT_SHIP_TILE_SANK,
		SHIP_TILE_SANK,
		GRIDINNACTIVE,
		GAMESTATUS
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