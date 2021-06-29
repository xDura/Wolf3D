#ifndef WF_WINDOW_H
#define WF_WINDOW_H
#include "wf_pch.h"

namespace Wolf 
{
	class Window
	{
	public:
		std::string title;
		unsigned int width;
		unsigned int height;
		unsigned int flags;

		Window(std::string a_title, unsigned int a_width, unsigned int a_height, unsigned int a_flags)
			: title(a_title), width(a_width), height(a_height), flags(a_flags)
		{}

		virtual ~Window() = default;
		virtual void OnUpdate() = 0;

		// Window attributes
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		virtual void* GetNativeWindowPtr() const = 0;
	};
}

#endif