#include <iostream>
#include "sdl_window.h"

int main(int argc, char* argv[])
{
    std::cout << "HELLO WORLD" << std::endl;
    Wolf::SDL_WINDOW* window = new Wolf::SDL_WINDOW();
    window->sdl_window = Wolf::SDL_WINDOW::Create("Wolf3D", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    std::cin.get();
    delete(window);
    return 0;
}