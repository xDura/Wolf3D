#ifndef WF_SDL_WINDOW_H
#define WF_SDL_WINDOW_H
#include "window.h"

namespace Wolf 
{
	class SDL_WINDOW : public Window 
	{
	public:
		SDL_Window* sdl_window;
		static SDL_Window* Create(const std::string& name, unsigned int width, unsigned int height);
		virtual ~SDL_WINDOW();
		virtual void OnUpdate() override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual void* GetNativeWindowPtr() const override;
	};

}

#endif //WF_SDL_WINDOW_H