#pragma once

#include "Button.h"

class MenuButton : public Button
{
public:
    void onClick() override
    {
        std::cout << "Click";
    }

    void update(sf::RenderWindow* window, bool mouseClicked) override
    {
        if (this->isCovered(window))
        {
            this->setNewCharSize(27);
            if (mouseClicked)
                this->onClick();
        }
        else this->setNewCharSize(25);
    }

    MenuButton(sf::Texture* texture, const std::string& bText, const sf::Vector2f& pos, int fontSize)
        : Button(texture, bText, pos, fontSize) 
    {
        
    }
    ~MenuButton() {}
};