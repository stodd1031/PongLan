#include "actor.hpp"

Actor::Actor(int width, int height, int x, int y, sf::Color color, sf::RenderWindow* window)
{
    mtx = new std::mutex();
    actor.setSize(sf::Vector2f(width, height));
    actor.setPosition(xLoc, yLoc);
    xLoc = (float)x / window->getSize().x * 1920;
    yLoc = (float)y / window->getSize().y * 1000;
    actor.setFillColor(color);
}

Actor::Actor()
{
    
}

void Actor::Update(sf::RenderWindow* window)
{
    xLoc += xVel;
    yLoc += yVel;
    actor.setPosition(xLoc, yLoc);
    window->draw(actor);
}

void Actor::setxVel(int vec)
{
    mtx->lock();
    xVel = vec;
    mtx->unlock();
}
void Actor::setyVel(int vec)
{
    mtx->lock();
    yVel = vec;
    mtx->unlock();
}
void Actor::setXLoc(int loc)
{
    mtx->lock();
    xLoc = loc;
    mtx->unlock();
}
void Actor::setYLoc(int loc)
{
    mtx->lock();
    yLoc = loc;
    mtx->unlock();
}

void Actor::swapxVel()
{
    mtx->lock();
    xVel *= -1;
    mtx->unlock();
    
}

void Actor::swapyVel()
{
    mtx->lock();
    yVel *= -1;
    mtx->unlock();
}

int Actor::getxVel()
{
    std::lock_guard<std::mutex> lock(*mtx);
    return xVel;
}
int Actor::getyVel()
{
    std::lock_guard<std::mutex> lock(*mtx);
    return yVel;
}
int Actor::getXLoc()
{
    std::lock_guard<std::mutex> lock(*mtx);
    return xLoc;
}
int Actor::getYLoc()
{
    std::lock_guard<std::mutex> lock(*mtx);
    return yLoc;
}