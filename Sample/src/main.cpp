#include <iostream>
#include "sdl_window.h"

int main(int argc, char* argv[])
{
    std::cout << "HELLO WORLD" << std::endl;
    Wolf::SDL_WINDOW::Create("Wolf3D", 30, 30);
    std::cin.get();
    return 0;
}