#pragma once


namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
}

namespace Textures
{
	enum class ID : uint8_t
	{
		MENU_BACKGROUND,
		BUTTON1,
		BUTTON2,
		BUTTON3,
		GAME_BACKGROUND,
		CONNECT_SCREEN,
		GRID,
		SELECTED_TILE,
		SHIP_TILE,
		HINT_SHIP_TILE_A,
		HINT_SHIP_TILE_I,
		HINT_BOARD_BACKGROUND
	};
}

namespace Sounds
{
	enum class ID : uint8_t
	{
		SOUND1
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
typedef ResourceManager<sf::SoundBuffer, Sounds::ID> SoundManager;