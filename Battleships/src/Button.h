#pragma once

#include <iostream>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum class ButtonID : uint8_t
{
	NONE,
	M_HOST,
	M_CONNECT,
	M_EXIT,
    C_CONNECT,
    C_HOST,
    C_BACK
};

class Button : public sf::Sprite
{
private:
    sf::Vector2f size = { 0,0 };    // object(sprite) size
    sf::Texture mTexture;           // sprite texture
    sf::Font text_font;             // font
    std::string text_string;        // text string
    int font_size;                  // font size
    bool signature_visible;         // is signature visible
    void initText(const std::string& b_text);
    void initButtonTexture(const sf::Texture& texture);
    sf::Text button_signature;      // button signature

public:
   

	/* constructor/ destructor */
	/* constructor should be called with the child class constructor like that : YourButton(T a, T b, T c, T d) : Button(a,b,c,d) */
	Button(const sf::Texture &texture, const std::string& bText, const sf::Vector2f& pos, const sf::Font& font, int fontSize);
	virtual ~Button();

    /* virtual methods that have to be overrided, onclick and update actions need to be handled in child class */
    virtual void onClick(sf::RenderWindow* window) = 0;
    virtual ButtonID update(sf::RenderWindow* window, bool mouseClicked) = 0;

    /* methods */
    bool isCovered(sf::RenderWindow* window);       // checks if button is covered by mouse
    void drawButton(sf::RenderWindow* window);      // draws sprite and text
    void setNewCharSize(int font_size);             // sets new font size and shifts text to the button center
    sf::Vector2f getSize(void);                     // returns button size
    void setSize(const sf::FloatRect& newSize);
    std::string getString(void);
    void setString(std::string);
    void set_color(const sf::Color& color);
    void set_signature_visiblity(bool flag);
};