#pragma once

#include "SFML/Graphics.hpp"

enum class HintAction
{
	ADD,
	REMOVE,
	SANK
};

class ShipHint
{
private:
	sf::RectangleShape mShipHints[10];
	bool mShipIdSank[10] = { false };
	sf::Texture* mInnactiveTexture;
	sf::Texture* mActiveTexture;
	sf::Texture* mSankTexture;
	sf::Vector2f mTileShift;

public:
	ShipHint();
	ShipHint(sf::Texture& texture, sf::Texture& texture2, sf::Texture& texture3, bool playerGrid);
	~ShipHint();

	void draw_ship_hints(sf::RenderWindow* window) const;
	void update_ship_hints(int shipId, HintAction action);
	void update_ship_hints(int shipId);
	void set_all_hints_active(void);
};