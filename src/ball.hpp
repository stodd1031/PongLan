#pragma once
#include "actor.hpp"
#include <stdlib.h>
#include "time.h"
#include "variables.hpp"

class Ball: public Actor
{
    public:
    
    Ball(int width, int height, int x, int y, sf::Color color, sf::RenderWindow* window);
    Ball();
    void Update(sf::RenderWindow *window);

    


};
