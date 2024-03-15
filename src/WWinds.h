#pragma once

#include "includes.h"
#include "stdarg.h"

typedef void (*UserRenderFunc)(int numArgs, va_list args);
uint16_t WND_CLASS_ID = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch(uMsg)
  {
    case WM_CLOSE:
      DestroyWindow(hwnd);
    break;
    case WM_DESTROY:
      PostQuitMessage(0);
    break;
    default:
      return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }
  return 0;
}

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
  
  RWL_Renderer RENDERER;
  UserRenderFunc RENDER_FUNC;

} RWIN;

// Main loop that happens every frame for window rendering
void RWL_RenderLoop(RWIN *window) {
  // Process messages in the message queue
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    // initiate user defined render function
    window->RENDER_FUNC(window->RENDERER.NUM_ARGS, window->RENDERER.CONTEXT);
  }
}

// set user defined function to the one being called in RWL_RenderLoop
void set_RenderFunc(RWIN *window, UserRenderFunc renderFunc, uint8_t numArgs, ...) {
  window->RENDER_FUNC = renderFunc;
  window->RENDERER.NUM_ARGS = numArgs;

  // variadic function stuffs for appying arguments to RENDERER.CONTEXT
  va_start(window->RENDERER.CONTEXT, numArgs);
  va_end(window->RENDERER.CONTEXT);
}

// Window creation for Windows OS systems
HWND RWL_CreateWWindow(RWIN *window) {

  // Register window class and set window procedure
  WNDCLASSEX wc = { 0 };
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = GetModuleHandle(NULL);
  wc.lpszClassName = window->S_CLASS_ID;
  wc.cbSize        = sizeof(WNDCLASSEX);
  wc.style         = 0;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
  wc.lpszMenuName  = NULL;
  wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
  if(!RegisterClassEx(&wc))
  {
    EXIT("WINDOW CLASS CREATION", NULL_AFTER_CREATION); // exit with error macro
  }

  // Create a window using WinAPI
  HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, window->S_CLASS_ID, window->TITLE, WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT, window->WIDTH, window->HEIGHT,
                              NULL, NULL, GetModuleHandle(NULL), NULL);
  if(hwnd == NULL)
  {
    EXIT("WINDOW CREATION", NULL_AFTER_CREATION); // exit with error macro
  }
  // Return the window handle
  return hwnd;
}

// Create RWL's window object
RWIN* RWL_CreateWindow(enum RESOLUTION resolution, const char title[]) {
  RWIN *window = (RWIN*)malloc(sizeof(RWIN));
  // increment global ID for window binding
  WND_CLASS_ID++;
  // "bind" an ID to the window
  window->CLASS_ID = WND_CLASS_ID;
  sprintf(window->S_CLASS_ID, "%d", window->CLASS_ID);
  fb_init(&window->FRAME_BUFFER);
  strcpy(window->TITLE, title);
  int width;
  int height;
  switch (resolution) {
    case 0:
      width = 1366;
      height = 768;
      break;
    case 1:
      width = 1920;
      height = 1080;
      break;
    case 2:
      break;
    case 3:
    break;
    default:
      printf("::WINDOW CREATION ERROR:: INVALID RESOLUTION");
  }
  window->WIDTH = width;
  window->HEIGHT = height;
  window->WINDOW = RWL_CreateWWindow(window);

  // Windows OS functions for showing the window
  ShowWindow(window->WINDOW, SW_SHOW);
  UpdateWindow(window->WINDOW);

  return window;
}

