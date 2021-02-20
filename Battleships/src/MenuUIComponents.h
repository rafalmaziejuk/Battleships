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

    ButtonId update(sf::RenderWindow* window, bool mouseClicked) override
    {
        if (this->isCovered(window))
        {
            this->setNewCharSize(27);
            if (mouseClicked)
            {
                this->onClick(window);
                if (getString() == "Host") return ButtonId::M_HOST;
                else if (getString() == "Connect") return ButtonId::M_CONNECT;
                else if (getString() == "Exit") return ButtonId::M_EXIT;
            }
        }
        else
        {
            this->setNewCharSize(25);
            return ButtonId::NONE;
        }
    }

    MenuButton(sf::Texture* texture, const std::string& bText, const sf::Vector2f& pos, int fontSize)
        : Button(texture, bText, pos, fontSize) 
    {
        
    }
    ~MenuButton() {}
};