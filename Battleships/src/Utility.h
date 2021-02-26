#pragma once

#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Utility
{
	template <typename T>
	std::string to_string(const T &value);

	template <typename T>
	sf::Vector2i to_vector2i(sf::Vector2<T> vector);

	void align_text_center(sf::Text &text);
	
	void cls(void);
	void console_cursor(bool flag);
}

#include "Utility.inl"