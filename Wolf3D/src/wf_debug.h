#ifndef WF_DEBUG_H
#define WF_DEBUG_H
#include "wf_pch.h"
#if _WIN32
#include "windows.h"
#endif
#define WF_ASSERT_ALWAYS(exp, msg) Wolf::Logger::DebugLogError("%s :  file: %s : line: %d", msg, __FILE__, __LINE__); while(true){};
#ifdef _DEBUG
#define WF_ASSERT(exp, msg) Wolf::Logger::DebugLogError("%s :  file: %s : line: %d", msg, __FILE__, __LINE__); abort();
#define WF_LOGERROR(...) Wolf::Logger::DebugLogError(__VA_ARGS__)
#define WF_LOGWARNING(...) Wolf::Logger::DebugLogWarning(__VA_ARGS__)
#define WF_LOG(...) Wolf::Logger::DebugLog(__VA_ARGS__)
#else
#define WF_ASSERT(exp) void(0)
#define WF_LOGERROR(...) Wolf::Logger::DebugLogError(__VA_ARGS__)
#define WF_WARNING(...) void(0)
#define WF_LOG(...) void(0)
#endif

namespace Wolf
{
	constexpr auto MAX_LOG_LEN = 1024;

	class Logger
	{
	public:
		static void DebugLog(const char* format, ...)
		{
			va_list args;
			va_start(args, format);
			char msg[MAX_LOG_LEN];
			vsnprintf(msg, (MAX_LOG_LEN - 2), format, args);
			strcat_s(msg, sizeof(msg), "\n");
			vprintf(msg, args);
			va_end(args);
		}

		static void DebugLogError(const char* format, ...)
		{
	#if _WIN32
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 12);
	#endif
			va_list args;
			va_start(args, format);
			char msg[MAX_LOG_LEN];
			vsnprintf(msg, (MAX_LOG_LEN - 2), format, args);
			strcat_s(msg, sizeof(msg), "\n");
			vprintf(msg, args);
			va_end(args);
	#if _WIN32
			SetConsoleTextAttribute(hConsole, 7);
	#endif
		}

		static void DebugLogWarning(const char* format, ...)
		{
	#if _WIN32
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 14);
	#endif
			va_list args;
			va_start(args, format);
			char msg[MAX_LOG_LEN];
			vsnprintf(msg, (MAX_LOG_LEN - 2), format, args);
			strcat_s(msg, sizeof(msg), "\n");
			vprintf(msg, args);
			va_end(args);
	#if _WIN32
			SetConsoleTextAttribute(hConsole, 7);
	#endif
		}
	};

}
#endif