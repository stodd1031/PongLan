#pragma once    

#include "actor.hpp"
#include "variables.hpp"

class Paddle: public Actor
{
    public:
    Paddle(int width, int height, int x, int y, sf::Color color, sf::RenderWindow* window);
    Paddle();
    void upPressed();
    void upReleased();
    void downPressed();
    void downReleased();
    void Update(sf::RenderWindow* window);

    // private:
    int moveSpeed = 10;
};