#include "wf_pch.h"
#include "sdl_window.h"

SDL_Window* Wolf::SDL_WINDOW::Create(const std::string& name, unsigned int width, unsigned int height)
{
	SDL_Window* window;

	//set attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); //16 or 24
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	//antialiasing (disable this lines if it goes too slow)
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, multisample); //increase to have smoother polygons

	SDL_Init(SDL_INIT_VIDEO /*| SDL_INIT_AUDIO*/);              // Initialize SDL2
	window = SDL_CreateWindow(
		"XDEngine",							// window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		width,								// width, in pixels
		height,								// height, in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	if (window == NULL)
		printf("Error creating window: %s\n", SDL_GetError());

	return window;
}

Wolf::SDL_WINDOW::~SDL_WINDOW()
{
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

void Wolf::SDL_WINDOW::OnUpdate(){}
void Wolf::SDL_WINDOW::SetVSync(bool enabled){}
bool Wolf::SDL_WINDOW::IsVSync() const
{
	return false;
}

void* Wolf::SDL_WINDOW::GetNativeWindowPtr() const
{
	return nullptr;
}
