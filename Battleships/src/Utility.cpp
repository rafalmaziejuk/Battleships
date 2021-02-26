#include <Windows.h>

#include "Utility.h"

void Utility::align_center(sf::Text &text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
}

void Utility::align_center(sf::Sprite &sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.0f), std::floor(bounds.top + bounds.height / 2.0f));
}

void Utility::cls(void)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD());
}

void Utility::console_cursor(bool flag)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = flag;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}