#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "MenuUIComponents.h"

class MenuState : public State
{
private:
	sf::Texture mBacgroundTexture;
	std::vector<sf::Texture*> mButtonTextures;
	std::vector<Button*> mButtons;
	sf::Sprite mBackground;
	bool mMouseClicked;

public:
	MenuState(sf::RenderWindow *window);
	virtual ~MenuState(void);

	void init_ui(void);
	virtual void render(void) override;
	virtual void update(sf::Time elapsedTime) override;
	virtual void handle_event(sf::Event &event) override;
};