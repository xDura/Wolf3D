#ifndef WF_APPLICATION_H
#define WF_APPLICATION_H
#include "window.h"

namespace Wolf 
{
	class Application
	{
	public:
		void Init(/*SDL_Window* a_window, SDL_GLContext* a_context*/);
		void StartUp();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void ShutDown();

		//static bool needsShutDown;
		//static float musicVolume;
		//static SDL_Window* window;
		//static SDL_GLContext* glContext;
		//static Window window;
		//static GraphicsContext context;
	};
}
#endif