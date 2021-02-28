#pragma once

#include <cstdint>

namespace States
{
	enum class ID : uint8_t
	{
		NONE,
		MAIN_MENU,
		CONNECT_HOST,
		CONNECT_JOIN,
		GAME_HOST,
		GAME_JOIN
	};
}