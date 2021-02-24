#include "Button.h"

/* constructor/ destructor */

Button::Button(const sf::Texture& texture, const std::string& bText, const sf::Vector2f& pos, const sf::Font& font, int fontSize)
{
	initButtonTexture(texture);
	setPosition(pos);
	text_string = bText;
	text_font = font;
	font_size = fontSize;
	initText(bText);
}

Button::~Button()
{

}

/* functions used to getting character and string size in pixels */

static int getLetterSize(char letter, sf::Font& font, int font_size)
{
    return int(font.getGlyph(int(letter), font_size, false).advance);
}

static int getTextLenghtInPixel(const std::string& b_text, int letter_size)
{
    return letter_size * b_text.length();
}

/* initialization */

void Button::initText(const std::string& b_text)
{
    button_signature.setString(b_text);
    button_signature.setFont(text_font);
    setNewCharSize(font_size);
}


void Button::initButtonTexture(const sf::Texture& tex)
{
    mTexture = tex;
    setTexture(mTexture);

    sf::Vector2f sprite_size = { getLocalBounds().width,getLocalBounds().height };
    size = sprite_size;
}


/* methods */

bool Button::isCovered(sf::RenderWindow* window)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*window);
    if ((mouse_pos.x >= getPosition().x && mouse_pos.x <= getPosition().x + getSize().x) && (mouse_pos.y >= getPosition().y && mouse_pos.y <= getPosition().y + getSize().y))
        return true;
    else return false;
}

void Button::drawButton(sf::RenderWindow* window)
{
    window->draw(*this);
    window->draw(button_signature);
}

void Button::setNewCharSize(int font_size)
{
    button_signature.setCharacterSize(font_size);
    int letter_size_x = getLetterSize(text_string[0], text_font, font_size);
    int text_size_x = getTextLenghtInPixel(text_string, letter_size_x);
    int letter_size_y = (int)button_signature.getLocalBounds().height;

    button_signature.setPosition(getPosition().x + getSize().x / 2.0f - text_size_x / 2.0f, getPosition().y + getSize().y / 2.0f - letter_size_y/2.0f);
}

sf::Vector2f Button::getSize(void)
{
    return size;
}

void Button::setSize(const sf::FloatRect& newSize)
{
    size = {newSize.width, newSize.height};
}

std::string Button::getString(void)
{
    return text_string;
}

void Button::set_color(const sf::Color& color)
{
    button_signature.setColor(color);
}