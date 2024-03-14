// platform.h
#pragma once

#ifdef _WIN32
#define PLATFORM_WINDOWS
#elif defined(__linux__)
#define PLATFORM_LINUX
#elif defined(__APPLE__)
#define PLATFORM_MACOS
#endif

#ifdef PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// Define your own window handle type
#ifdef PLATFORM_WINDOWS
typedef HWND WindowHandle;
#endif
#ifdef PLATFORM_WINDOWS
#include "WWinds.h"
#endif