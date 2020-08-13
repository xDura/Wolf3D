/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2020 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL_config_h_
    #include "SDL_platform.h"
    #if defined(ANDROID) || defined(__ANDROID__)
        #include "SDL_config_android.h"
    #elif defined(__APPLE__)
        #include "SDL_config_macosx.h"
    #elif defined(__linux__)
        #include "SDL_config_linux.h"
    #elif defined(_WIN32)
        #include "SDL_config_windows.h"
    #else
        #pragma message ("SDL PLATFORM MISSING!")
    #endif
#endif