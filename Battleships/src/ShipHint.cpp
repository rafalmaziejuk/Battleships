#include "ShipHint.h"

ShipHint::ShipHint() 
{
	
}

ShipHint::ShipHint(sf::Texture& texture, sf::Texture& texture2, sf::Texture& texture3, bool playerGrid)
	: mInnactiveTexture(&texture), mActiveTexture(&texture2), mSankTexture(&texture3)
{

	if (!playerGrid)
		mTileShift = { 605,0 };
	else mTileShift = { 0,0 };

	// hint ships configuration 
	mInnactiveTexture->setRepeated(true);
	mActiveTexture->setRepeated(true);
	mSankTexture->setRepeated(true);

	mShipHints[0].setSize(sf::Vector2f(30, 30));
	mShipHints[0].setPosition(490 + mTileShift.x, 620);
	mShipHints[0].setTextureRect(sf::IntRect(0, 0, 30, 30));
	mShipHints[0].setTexture(mInnactiveTexture);

	mShipHints[1].setSize(sf::Vector2f(30, 30));
	mShipHints[1].setPosition(370 + mTileShift.x, 680);
	mShipHints[1].setTextureRect(sf::IntRect(0, 0, 30, 30));
	mShipHints[1].setTexture(mInnactiveTexture);

	mShipHints[2].setSize(sf::Vector2f(30, 30));
	mShipHints[2].setPosition(430 + mTileShift.x, 680);
	mShipHints[2].setTextureRect(sf::IntRect(0, 0, 30, 30));
	mShipHints[2].setTexture(mInnactiveTexture);

	mShipHints[3].setSize(sf::Vector2f(30, 30));
	mShipHints[3].setPosition(490 + mTileShift.x, 680);
	mShipHints[3].setTextureRect(sf::IntRect(0, 0, 30, 30));
	mShipHints[3].setTexture(mInnactiveTexture);

	mShipHints[4].setSize(sf::Vector2f(60, 30));
	mShipHints[4].setPosition(100 + mTileShift.x, 680);
	mShipHints[4].setTextureRect(sf::IntRect(0, 0, 60, 30));
	mShipHints[4].setTexture(mInnactiveTexture);

	mShipHints[5].setSize(sf::Vector2f(60, 30));
	mShipHints[5].setPosition(190 + mTileShift.x, 680);
	mShipHints[5].setTextureRect(sf::IntRect(0, 0, 60, 30));
	mShipHints[5].setTexture(mInnactiveTexture);

	mShipHints[6].setSize(sf::Vector2f(60, 30));
	mShipHints[6].setPosition(280 + mTileShift.x, 680);
	mShipHints[6].setTextureRect(sf::IntRect(0, 0, 60, 30));
	mShipHints[6].setTexture(mInnactiveTexture);

	mShipHints[7].setSize(sf::Vector2f(90, 30));
	mShipHints[7].setPosition(250 + mTileShift.x, 620);
	mShipHints[7].setTextureRect(sf::IntRect(0, 0, 90, 30));
	mShipHints[7].setTexture(mInnactiveTexture);

	mShipHints[8].setSize(sf::Vector2f(90, 30));
	mShipHints[8].setPosition(370 + mTileShift.x, 620);
	mShipHints[8].setTextureRect(sf::IntRect(0, 0, 90, 30));
	mShipHints[8].setTexture(mInnactiveTexture);

	mShipHints[9].setSize(sf::Vector2f(120, 30));
	mShipHints[9].setPosition(100 + mTileShift.x, 620);
	mShipHints[9].setTextureRect(sf::IntRect(0,0,120,30));
	mShipHints[9].setTexture(mInnactiveTexture);
	
}

ShipHint::~ShipHint() 
{

}

void ShipHint::draw_ship_hints(sf::RenderWindow* window) const
{
	for(unsigned i = 0 ; i < 10 ; i++)
		window->draw(mShipHints[i]);
}

void ShipHint::update_ship_hints(int shipId,HintAction action)
{
	if (action == HintAction::ADD)
	{
		//mShipHints[shipId].setFillColor(sf::Color(126,227,39));
		mShipHints[shipId].setTexture(mActiveTexture);
	}
	else if (action == HintAction::REMOVE)
	{
		mShipHints[shipId].setTexture(mInnactiveTexture);
	}
	else if (action == HintAction::SANK)
	{
		mShipHints[shipId].setTexture(mSankTexture);
		mShipIdSank[shipId] = true;
	}
}

void ShipHint::update_ship_hints(int shipLenght)
{
	int start = 0;
	int end = 0;
	switch (shipLenght)
	{
		case 1: start = 0; end = 3; break;
		case 2: start = 4; end = 6; break;
		case 3: start = 7; end = 8; break;
		case 4: start = 9; end = 9; break;
	}
	int id = start;

	while (id <= end)
	{
		if (!mShipIdSank[id])
		{
			mShipHints[id].setTexture(mSankTexture);
			mShipIdSank[id] = true;
			return;
		}
		id++;
	}
}

void ShipHint::set_all_hints_active(void)
{
	for(unsigned i = 0 ; i < 10 ; i++)
		mShipHints[i].setTexture(mActiveTexture);
}