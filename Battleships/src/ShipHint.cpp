#include "ShipHint.h"

ShipHint::ShipHint() 
{
	
}

ShipHint::ShipHint(sf::Texture& texture, sf::Texture& texture2)
	: mInnactiveTexture(&texture), mActiveTexture(&texture2)
{
	// hint ships configuration 
	mInnactiveTexture->setRepeated(true);
	mActiveTexture->setRepeated(true);

	mShipHints[0].setSize(sf::Vector2f(30, 30));
	mShipHints[0].setPosition(490, 620);
	mShipHints[0].setTextureRect(sf::IntRect(0, 0, 30, 30));
	mShipHints[0].setTexture(mInnactiveTexture);

	mShipHints[1].setSize(sf::Vector2f(30, 30));
	mShipHints[1].setPosition(370, 680);
	mShipHints[1].setTextureRect(sf::IntRect(0, 0, 30, 30));
	mShipHints[1].setTexture(mInnactiveTexture);

	mShipHints[2].setSize(sf::Vector2f(30, 30));
	mShipHints[2].setPosition(430, 680);
	mShipHints[2].setTextureRect(sf::IntRect(0, 0, 30, 30));
	mShipHints[2].setTexture(mInnactiveTexture);

	mShipHints[3].setSize(sf::Vector2f(30, 30));
	mShipHints[3].setPosition(490, 680);
	mShipHints[3].setTextureRect(sf::IntRect(0, 0, 30, 30));
	mShipHints[3].setTexture(mInnactiveTexture);

	mShipHints[4].setSize(sf::Vector2f(60, 30));
	mShipHints[4].setPosition(100, 680);
	mShipHints[4].setTextureRect(sf::IntRect(0, 0, 60, 30));
	mShipHints[4].setTexture(mInnactiveTexture);

	mShipHints[5].setSize(sf::Vector2f(60, 30));
	mShipHints[5].setPosition(190, 680);
	mShipHints[5].setTextureRect(sf::IntRect(0, 0, 60, 30));
	mShipHints[5].setTexture(mInnactiveTexture);

	mShipHints[6].setSize(sf::Vector2f(60, 30));
	mShipHints[6].setPosition(280, 680);
	mShipHints[6].setTextureRect(sf::IntRect(0, 0, 60, 30));
	mShipHints[6].setTexture(mInnactiveTexture);

	mShipHints[7].setSize(sf::Vector2f(90, 30));
	mShipHints[7].setPosition(250, 620);
	mShipHints[7].setTextureRect(sf::IntRect(0, 0, 90, 30));
	mShipHints[7].setTexture(mInnactiveTexture);

	mShipHints[8].setSize(sf::Vector2f(90, 30));
	mShipHints[8].setPosition(370, 620);
	mShipHints[8].setTextureRect(sf::IntRect(0, 0, 90, 30));
	mShipHints[8].setTexture(mInnactiveTexture);

	mShipHints[9].setSize(sf::Vector2f(120, 30));
	mShipHints[9].setPosition(100, 620);
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
}