# Ryan's Windowing Library (RWL) - WORK IN PROGRESS

## Purpose

I am making this simple library mostly as a learning project for myself to better understand the win32 api, but also as a much simpler version of something like SDL/GLFW. 
The purpose of this library is to provide a simple API for creating, interacting, and displaying visuals with windows. Right now it just aims to provide support for Windows OS systems.

## Scope

- Abstract away the need for a WinMain function
- Abstract away the details of Window Creation
- Abstract away the render loop
- Simplify input handling
- Provide support for both CPU and GPU graphics backends
- Provide simple primitive draw commands (triangle, square, line, etc.)

## Current Features

### Main function
There is no need for a WinMain function, a simple main function in c/c++ will do.

### Window Creation and Use
Window creation is simplified as shown:
```c
RWIN *WIN = RWL_CreateWindow(HD768, "My Title"); // create window with standard hd resolution and title
set_RenderFunc(WIN, render, 0); // attatch render callback
RWL_RenderLoop(WIN); //main loop
```
With three simple steps you create the window, attatch a render function to the window, and then start the window's render loop. 
- The window creation function takes two inputs, a standard resolution (HD768, HD1080, etc.) 
and a title to go into the title bar of the window.
- You attatch a render function of your creation to the window via the set render function, your function will be called every frame of the render loop, so whatever you 
want to happen in the render loop just place in the function.
- You initiate the render loop of the function with the render loop function, you can create as many windows as you want up to 256, and specify wich window you
want to start rendering to.

The details of each function and use can be found further down in the documentation.

## Demo

The example code is used to create two windows, WIN and WIN2. And then setting two different render functions render and render2 to WIN and WIN2 respectively. 
The first window is just set to print "rendered" to stdout, and the second window is given two extra parameters in the set render function and the window prints these parameter to stdout.
The code being used:
```c
#include "includes.h"

void render(int numArgs, va_list args) {
  printf("rendered\n");
}
void render2(int numArgs, va_list args) {
  for (int i = 0; i < numArgs; i++) {
    printf("%d\n", va_arg(args, int));
  }
}

int main() {
  RWIN *WIN = RWL_CreateWindow(HD768, "My Title"); // create window with standard hd resolution and title
  set_RenderFunc(WIN, render, 0); // attatch render callback
  RWL_RenderLoop(WIN); //main loop

  RWIN *WIN2 = RWL_CreateWindow(HD768, "\0");
  set_RenderFunc(WIN2, render2, 2, 13, 3);
  RWL_RenderLoop(WIN2);
  free(WIN);
  free(WIN2);

  return 0;
}
```
And the demo:
<img src='https://github.com/NayrMu/Ryans-Windowing-Library/blob/main/RWL-Demo-1.gif' title='Video Demo' width='' alt='Video Demo' />

