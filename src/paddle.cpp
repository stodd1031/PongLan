#include "paddle.hpp"

Paddle::Paddle(int width, int height, int x, int y, sf::Color color, sf::RenderWindow* window)
: Actor(width, height, x, y, color, window)
{
    if (actor.getPosition().x < 0)
    {
        actor.setPosition(0, actor.getPosition().y);
    }
    else if (actor.getPosition().x + actor.getSize().x > width)
    {
        actor.setPosition(width - actor.getSize().x, actor.getPosition().y);
    }
}

Paddle::Paddle()
{
    
}

void Paddle::upPressed()
{
    yVel -= moveSpeed / 1000.0f * height;
}

void Paddle::upReleased()
{
    yVel += moveSpeed / 1000.0f * height;;
}

void Paddle::downPressed()
{
    yVel += moveSpeed / 1000.0f * height;;
}

void Paddle::downReleased()
{
    yVel -= moveSpeed / 1000.0f * height;
    actor.setPosition(20, actor.getPosition().y);
}

void Paddle::Update(sf::RenderWindow* window)
{
    xLoc += xVel;
    yLoc += yVel;
    if (yLoc < 0)
    {
        yLoc = 0;
    }
    else if (yLoc + actor.getSize().y > height)
    {
        yLoc = height - actor.getSize().y;
    }
    // std::cout << "x: " << xLoc << " y: " << yLoc << std::endl;
    actor.setPosition(xLoc, yLoc);
    window->draw(actor);
}