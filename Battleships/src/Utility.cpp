#include <Windows.h>

#include "Utility.h"

namespace Utility
{
	void set_origin_to_center(sf::Text &text)
	{
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
	}

	void set_origin_to_center(sf::Sprite &sprite)
	{
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
	}

	void cls(void)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD());
	}

	void console_cursor(bool flag)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
		cursorInfo.bVisible = flag;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}

	void copy_grid(bool src[10][10], bool dst[10][10])
	{
		for (unsigned i = 0; i < 10; i++)
			for (unsigned j = 0; j < 10; j++)
				dst[i][j] = src[i][j];
	}
}