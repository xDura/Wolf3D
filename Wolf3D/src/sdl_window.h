#ifndef WF_SDL_WINDOW_H
#define WF_SDL_WINDOW_H
#include "wf_debug.h"
#include "wf_window.h"

namespace Wolf 
{
	class SDL_WINDOW : public Window 
	{
	public:
		SDL_Window* sdl_window;

		SDL_WINDOW(const std::string& name, unsigned int width, unsigned int height, unsigned int flags) 
			: Window(name, width, height, flags)
		{
			SDL_Window* window;

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
				name.c_str(),						// window title
				SDL_WINDOWPOS_UNDEFINED,			// initial x position
				SDL_WINDOWPOS_UNDEFINED,			// initial y position
				width,								// width, in pixels
				height,								// height, in pixels
				flags
			);

			if (window == NULL) 
			{
				WF_LOGERROR("Error creating window: %s\n", SDL_GetError());
			}

			sdl_window = window;
		}
		//static SDL_Window* Create(const std::string& name, unsigned int width, unsigned int height, unsigned int flags);
		virtual ~SDL_WINDOW();
		virtual void OnUpdate() override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual void* GetNativeWindowPtr() const override;
	};

}

#endif //WF_SDL_WINDOW_H