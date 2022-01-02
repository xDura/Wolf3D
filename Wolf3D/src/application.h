#ifndef WF_APPLICATION_H
#define WF_APPLICATION_H
#include "wf_window.h"

namespace Wolf 
{
	class Application
	{
	public:
		Application(Window* a_window)
		{
			window = a_window;
		}

		void StartUp();
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void ShutDown();

		static bool needsShutDown;
		static Window* window;
		//static GraphicsContext context;
	};
}
#endif