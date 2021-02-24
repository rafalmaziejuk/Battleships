#pragma once

#include "Button.h"
#include "GameState.h"
#include "StateManager.h"

class ConnectButton : public Button
{
public:
    void onClick(sf::RenderWindow* window) override
    {
        std::cout << "Click";

    }

    ButtonID update(sf::RenderWindow* window, bool mouseClicked) override
    {
        if (this->isCovered(window))
        {
            if (getString() == "Back")
                setScale(1.05f, 1.05f);
            this->setNewCharSize(27);
            if (mouseClicked)
            {
                this->onClick(window);
                if (getString() == "Connect") return ButtonID::C_CONNECT;
                if (getString() == "Host") return ButtonID::C_HOST;
                if (getString() == "Back") return ButtonID::C_BACK;

            }
        }
        else
        {
            if (getString() == "Back")
                setScale(1.0f, 1.0f);
            this->setNewCharSize(25);
        }
        return ButtonID::NONE;
    }

    ConnectButton(const sf::Texture& texture, const std::string& bText, const sf::Vector2f& pos, const sf::Font& font, int fontSize)
        : Button(texture, bText, pos, font, fontSize)
    {
        if (bText == "Back")
            setOrigin(sf::Vector2f(getSize().x/2.0f, getSize().y/2.0f));
    }
    ~ConnectButton() { }
};