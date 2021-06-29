#include "wf_pch.h"
#include "sdl_window.h"

Wolf::SDL_WINDOW::~SDL_WINDOW()
{
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

void Wolf::SDL_WINDOW::OnUpdate(){}
void Wolf::SDL_WINDOW::SetVSync(bool enabled)
{
	int interval = 0;
	if (enabled) interval = -1;
	SDL_GL_SetSwapInterval(interval);
}

bool Wolf::SDL_WINDOW::IsVSync() const
{
	int interval = SDL_GL_GetSwapInterval();
	if (interval == 0) return false;
	else return true;
}

void* Wolf::SDL_WINDOW::GetNativeWindowPtr() const
{
	return (void*)sdl_window;
}
