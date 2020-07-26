#ifndef WF_WINDOW_H
#define WF_WINDOW_H
#include "wf_pch.h"

namespace Wolf 
{
	class Window
	{
	public:
		std::string title;
		int width;
		int height;

		virtual ~Window() = default;
		virtual void OnUpdate() = 0;

		// Window attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindowPtr() const = 0;
	};
}

#endif