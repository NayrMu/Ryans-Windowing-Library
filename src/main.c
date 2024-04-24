#include "WWinds.h"
#include "draw.h"
#include "Platform.h"


/*
* TODO:
* - Set up a copy to sytem to fame buffer function
* - Seperate source and header
*
*/


void render(int numArgs, va_list args) {
  COLORREF color = RGB(200, 130, 20);
  POINT point1 = {500, 300};
  POINT point2 = {300, 600};
  POINT point3 = {800, 600};
  RWIN* win = va_arg(args, RWIN*);
  RWL_Draw_Rect(win, 3, 3, 100, 100, color);
  RWL_Draw_Tri(win, point1, point2, point3, color);
  printf("rendered\n");
}
void render2(int numArgs, va_list args) {
  for (int i = 0; i < numArgs; i++) {
    printf("%d\n", va_arg(args, int));
  }
}

int main() {
  RWIN *WIN = RWL_CreateWindow(HD768, "My Title"); // create window with standard hd resolution and title

  RWL_Set_RenderFunc(WIN, render, 1, WIN); // attatch render callback
  RWL_RenderLoop(WIN); //main loop

  RWIN *WIN2 = RWL_CreateWindow(HD768, "\0");
  RWL_Set_RenderFunc(WIN2, render2, 2, 13, 3);
  RWL_RenderLoop(WIN2);
  free(WIN);
  free(WIN2);

  return 0;
}