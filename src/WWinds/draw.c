#include "draw.h"

void RWL_Draw_Rect(RWIN* window, uint16_t x, uint16_t y, uint16_t width, uint16_t height, COLORREF color) {
  RECT rect;
  SetRect(&rect, x, y, x+width, y+height);
  HBRUSH hBrush = CreateSolidBrush(color);
  SelectObject(window->offscreenDC, hBrush);
  FillRect(window->offscreenDC, &rect, hBrush);
  DeleteObject(hBrush);
}

void RWL_Draw_Tri(RWIN *window, POINT point1, POINT point2, POINT point3, COLORREF color) {
  POINT pArr[3];
  pArr[0] = point1;
  pArr[1] = point2;
  pArr[2] = point3;
  
  HRGN triangle = CreatePolygonRgn(pArr, 3, WINDING);
  HBRUSH hBrush = CreateSolidBrush(color);
  SelectObject(window->offscreenDC, hBrush);
  FillRgn(window->offscreenDC, triangle, hBrush);
  DeleteObject(hBrush);
}