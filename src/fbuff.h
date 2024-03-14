#pragma once

#include "stdint.h"
#include "stdlib.h"

typedef struct {
  uint8_t *buffer;
  uint64_t size;
  uint64_t end;
} fbuff;

void fb_init(fbuff* fbuff) {
  fbuff->size = 0;
  fbuff->end = 0;
}
void fb_pushback(fbuff *fbuff, uint8_t item) {
  if (fbuff->size == 0) { // if empty
    fbuff->buffer = (uint8_t*)malloc(sizeof(uint8_t)); // allocate
    fbuff->size = 1; // change size
    fbuff->end = 0; // change end
  }
  else {
    if (fbuff->end == fbuff->size - 1) { // if the buffer is filled
      fbuff->buffer = (uint8_t*)realloc(fbuff->buffer, (fbuff->size + 1) * sizeof(uint8_t)); // reallocate to size + 1 bytes
      fbuff->size ++; // change size
    }
    fbuff->end ++; // change end
  }
  fbuff->buffer[fbuff->end] = item; // add item
}