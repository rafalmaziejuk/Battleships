#pragma once

#include "SFML/Graphics.hpp"

enum class HintAction
{
	ADD,
	REMOVE
};

class ShipHint
{
private:
	sf::RectangleShape mShipHints[10];
	sf::Texture* mInnactiveTexture;
	sf::Texture* mActiveTexture;

public:
	ShipHint();
	ShipHint(sf::Texture& texture, sf::Texture& texture2);
	~ShipHint();

	void draw_ship_hints(sf::RenderWindow* window) const;
	void update_ship_hints(const int shipId, HintAction action);

};