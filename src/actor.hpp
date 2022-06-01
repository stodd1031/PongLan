#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "variables.hpp"
#include <mutex>

class Actor
{
public:
    Actor(int width, int height, int x, int y, sf::Color color, sf::RenderWindow* window);
    Actor();
    void Update(sf::RenderWindow *window);

    sf::RectangleShape actor;

    std::mutex *mtx;

    int xVel = 0;
    int yVel = 0;
    int xLoc;
    int yLoc;

    void setxVel(int vec);
    void setyVel(int vec);
    void setXLoc(int loc);
    void setYLoc(int loc);

    void swapxVel();
    void swapyVel();

    int getxVel();
    int getyVel();
    int getXLoc();
    int getYLoc();
};
