#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

namespace Utility
{
	template <typename T>
	std::string to_string(const T &value);

	template <typename T>
	sf::Vector2i to_vector2i(sf::Vector2<T> vector);

	void set_origin_to_center(sf::Text &text);
	void set_origin_to_center(sf::Sprite &sprite);
	
	void cls(void);
	void console_cursor(bool flag);
}

#include "Utility.inl"