
#include "WWinds.h"

/********************
Nomenclature Guide

helper-functions: start with hi_ for helper internal
user-functions: rwl_ to signify they are specifically from this API
internal facing functions: start with just i_ for internal


*********************/

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

void i_Init_Offscreen_Buffer(HWND hWnd, RWIN* window) {
    HDC hdc = GetDC(hWnd);
    window->offscreenDC = CreateCompatibleDC(hdc);
    window->offscreenBitmap = CreateCompatibleBitmap(hdc, window->WIDTH, window->HEIGHT);
    SelectObject(window->offscreenDC, window->offscreenBitmap);
    ReleaseDC(hWnd, hdc);
}
void i_Update_Window(HDC windowDC, RWIN* window) {
    BitBlt(windowDC, 0, 0, window->WIDTH, window->HEIGHT, window->offscreenDC, 0, 0, SRCCOPY);
}

// Main loop that happens every frame for window rendering
void RWL_RenderLoop(RWIN *window) {
  // Process messages in the message queue
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    // initiate user defined render function
    window->RENDER_FUNC(window->RENDERER.NUM_ARGS, window->RENDERER.CONTEXT);

    
    i_Update_Window(GetDC(GetActiveWindow()), window);
  }
}

// set user defined function to the one being called in RWL_RenderLoop
void RWL_Set_RenderFunc(RWIN *window, UserRenderFunc renderFunc, uint8_t numArgs, ...) {
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
    EXIT("WNDCLASS CREATION", NULL_AFTER_CREATION); // exit with error macro
  }

  // Create a window using WinAPI
  HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, window->S_CLASS_ID, window->TITLE, WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT, window->WIDTH, window->HEIGHT,
                              NULL, NULL, GetModuleHandle(NULL), NULL);
  if(hwnd == NULL)
  {
    EXIT("HWND CREATION", NULL_AFTER_CREATION); // exit with error macro
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
  int width = hi_create_width(resolution);
  int height = hi_create_height(resolution);
  
  window->WIDTH = width;
  window->HEIGHT = height;
  window->WINDOW = RWL_CreateWWindow(window);

  // Windows OS functions for showing the window
  ShowWindow(window->WINDOW, SW_SHOW);
  UpdateWindow(window->WINDOW);

  i_Init_Offscreen_Buffer(GetActiveWindow(), window);

  return window;
}

int hi_create_width(enum RESOLUTION resolution) {
  switch (resolution) {
    case 0:
      return 1366;
      break;
    case 1:
      return 1920;
      break;
    case 2:
      break;
    case 3:
    break;
    default:
      EXIT("WINDOW CREATION RESOLUTION", INVALID_INPUT);
  }
}

int hi_create_height(enum RESOLUTION resolution) {
  switch (resolution) {
    case 0:
      return 768;
      break;
    case 1:
      return 1080;
      break;
    case 2:
      break;
    case 3:
    break;
    default:
      EXIT("WINDOW CREATION RESOLUTION", INVALID_INPUT);
  }

}

