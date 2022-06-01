#include "button.hpp"

Button::Button(int width, int height, int x, int y, std::string buttonTextI, sf::Font *fontI)
{

    // std::cout << "make:" << this << std::endl;
    rectangle.setPosition(sf::Vector2f(x, y));
    rectangle.setSize(sf::Vector2f(width, height));

    font = fontI;

    textBox = sf::Text(buttonTextI, *font, 30);
    if (buttonTextI == "")
    {
        textBox.setString("A");
    }
    textBox.setFillColor(sf::Color::Black);
    textBox.setPosition(sf::Vector2f(
        (rectangle.getPosition().x + width / 2) - textBox.getGlobalBounds().width/2,
        (rectangle.getPosition().y + height / 2) - textBox.getGlobalBounds().height
    ));
    if (buttonTextI == "")
    {
        textBox.setString("");
    }
    
    
}//

Button::~Button()
{
    // std::cout << "deleter:" << this << std::endl;

}

void Button::update(sf::RenderWindow *window)
{

    window->draw(rectangle);
    window->draw(textBox);
}