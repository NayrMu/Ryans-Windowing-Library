#pragma once

#include "../Platform.h"
#include "../rerror.h"
#include "stdint.h"
#include "stdarg.h"
#include "../Fbuff/fbuff.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

typedef void (*UserRenderFunc)(int numArgs, va_list args);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Common resolutions to be given to RWL_CreateWindow function
enum RESOLUTION {
  HD768,
  HD1080,
  UHD2K,
  UHD4k,
};

// Struct that holds arg information for render function
typedef struct {
  uint8_t NUM_ARGS;
  va_list CONTEXT;

} RWL_Renderer;

// Struct for all window information including actual window and window calss
typedef struct {
  char TITLE[1];
  int16_t WIDTH;
  int16_t HEIGHT;

  WNDCLASSEX WINDOW_CLASS;
  uint16_t CLASS_ID;
  char S_CLASS_ID[3];
  HWND WINDOW;

  fbuff FRAME_BUFFER;
  HDC offscreenDC;
  HBITMAP offscreenBitmap;
  RECT clientRect;
  
  RWL_Renderer RENDERER;
  UserRenderFunc RENDER_FUNC;

} RWIN;

// Main loop that happens every frame for window rendering
void RWL_RenderLoop(RWIN *window);

// set user defined function to the one being called in RWL_RenderLoop
void RWL_Set_RenderFunc(RWIN *window, UserRenderFunc renderFunc, uint8_t numArgs, ...);

// Window creation for Windows OS systems
HWND RWL_CreateWWindow(RWIN *window);

// Create RWL's window object
RWIN* RWL_CreateWindow(enum RESOLUTION resolution, const char title[]);

int hi_create_width(enum RESOLUTION resolution);

int hi_create_height(enum RESOLUTION resolution);

void i_Init_Offscreen_Buffer(HWND hWnd, RWIN* window);

void RWL_Draw_Rect(RWIN* window, uint16_t x, uint16_t y, uint16_t width, uint16_t height, COLORREF color);

