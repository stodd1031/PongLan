#include "paddle.hpp"
#include "ball.hpp"
#include "pong.hpp"

const unsigned short loopsSecond = 60;
const unsigned short wait = 1000000 / loopsSecond;
unsigned short width = 1920;
unsigned short height = 1040;

int main()
{

    Pong pong;
    pong.mainLoop();

    return EXIT_SUCCESS;
}
