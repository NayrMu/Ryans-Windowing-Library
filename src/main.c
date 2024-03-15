#include "includes.h"


/*
* TODO:
* - Figure out how to get a byte array into windowproc for copying image to window
* - Is there another way to render to window?
* - Null checks
*
*
*/


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

  fbuff fbuff = WIN->FRAME_BUFFER;

  set_RenderFunc(WIN, render, 0); // attatch render callback
  RWL_RenderLoop(WIN); //main loop

  RWIN *WIN2 = RWL_CreateWindow(HD768, "\0");
  set_RenderFunc(WIN2, render2, 2, 13, 3);
  RWL_RenderLoop(WIN2);
  free(WIN);
  free(WIN2);

  return 0;
}