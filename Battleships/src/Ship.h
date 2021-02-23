#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Ship
{
private:

	sf::Vector2i mStart;
	sf::Vector2i mEnd;

private:
	uint8_t mLength = 0;
	bool mIsOnGrid = false;


	void update_grid_fields(sf::Vector2i&& shipSegment, bool** gridFields);
	void update_unavailable_fields(sf::Vector2i&& shipSegment, bool** gridFields, bool** unavailableFields);
	void update_unavailable_fields(bool** gridFields, bool** unavailableFields);
	void update_tile_area(const sf::Vector2i& pos, bool** unavailableFields);
public:
	Ship(void);

	~Ship(void);

	void set_length(uint8_t length);
	void set_position(sf::Vector2i start, sf::Vector2i end);
	sf::Vector2i get_start(void) const;
	sf::Vector2i get_end(void) const;
	uint8_t get_length(void) const;
	bool is_on_grid(void) const;

};

