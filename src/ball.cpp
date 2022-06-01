#include "ball.hpp"

Ball::Ball(int width, int height, int x, int y, sf::Color color, sf::RenderWindow* window)
    : Actor(width, height, x, y, color, window)
{
    
}

Ball::Ball()
{
}

void Ball::Update(sf::RenderWindow* window)
{
    mtx->lock();
    xLoc += xVel;
    // std::cout << xVel << std::endl;
    yLoc += yVel;
    if (yLoc < 0)
    {
        yLoc = 0;
        yVel *= -1;
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() << std::endl;
    }
    else if (yLoc + actor.getSize().y > height)
    {
        yLoc = height - actor.getSize().y;
        yVel *= -1;
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() << std::endl;
    }
    actor.setPosition(xLoc, yLoc);
    mtx->unlock();
    window->draw(actor);
}

