#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"
#include "MenuUIComponents.h"
#include "Client.h"
#include "Server.h"
#


class MenuState : public State
{
private:
	std::vector<Button *> mButtons;
	sf::Sprite mBackground;
	bool mMouseClicked;
	ButtonID mButtonClicked;

public:
	MenuState(Context context);
	virtual ~MenuState(void);

	virtual void render(void) override;
	virtual void update(sf::Time elapsedTime) override;
	virtual void handle_event(const sf::Event &event) override;
};