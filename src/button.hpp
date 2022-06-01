#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Button
{
public:
    Button(int width, int height, int x, int y, std::string buttonText, sf::Font *fontI);
    ~Button();
    // std::string buttonText;
    void update(sf::RenderWindow *window);
    sf::RectangleShape rectangle;
    sf::Font *font;
    // std::unique_ptr<sf::Font> font;
    sf::Text textBox;
};