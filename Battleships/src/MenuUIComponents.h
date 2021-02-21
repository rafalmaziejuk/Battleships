#pragma once

#include "Button.h"
#include "GameState.h"
#include "StateManager.h"

class MenuButton : public Button
{
public:
    void onClick(sf::RenderWindow* window) override
    {
        //std::cout << "Click";
        
    }

    ButtonID update(sf::RenderWindow* window, bool mouseClicked) override
    {
        if (this->isCovered(window))
        {
            this->setNewCharSize(27);
            if (mouseClicked)
            {
                this->onClick(window);
                if (getString() == "Host") return ButtonID::M_HOST;
                else if (getString() == "Connect") return ButtonID::M_CONNECT;
                else if (getString() == "Exit") return ButtonID::M_EXIT;
            }
        }
        else
        {
            this->setNewCharSize(25);
            return ButtonID::NONE;
        }
    }

    MenuButton(const sf::Texture& texture, const std::string& bText, const sf::Vector2f& pos, const sf::Font &font, int fontSize)
        : Button(texture, bText, pos, font, fontSize) 
    {
        
    }
    ~MenuButton() { }
};