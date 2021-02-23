#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class Orientation
{
	Horizontal, Vertical
};

class Ship
{
private:

	sf::Vector2i mStart;
	sf::Vector2i mEnd;
	Orientation mOrientation;

private:
	uint8_t mLength = 0;
	bool mIsOnGrid = false;
	std::vector<sf::Sprite>mTiles;

public:
	Ship(void);

	~Ship(void);

	void set_length(uint8_t length);
	void set_position(sf::Vector2i start, sf::Vector2i end);
	sf::Vector2i get_start(void) const;
	sf::Vector2i get_end(void) const;
	uint8_t get_length(void) const;
	bool is_on_grid(void) const;
	bool contain_tile(const sf::Vector2i& cursorPos) const;
};

