#pragma once

#include "rerror.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct {
  uint8_t *buffer;
  uint64_t size;
  uint64_t end;
} fbuff;

void fb_init(fbuff* fbuff) {
  if (fbuff == NULL) {
    SOFT_EXIT("rb_resize", NULL_PARAM);
  }
  fbuff->size = 0;
  fbuff->end = 0;
}
void fb_pushback(fbuff *fbuff, uint8_t item) {
  if (fbuff->buffer == NULL) {
    SOFT_EXIT("rb_resize", NULL_PARAM);
  }
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
void fb_clear(fbuff *fbuff, uint8_t item) {
  if (fbuff == NULL) {
    SOFT_EXIT("rb_resize", NULL_PARAM);
  }
  for (int i = 0; i < fbuff->size; i++) {
    fbuff->buffer[i] = item;
  }
}
void fb_reset(fbuff *fbuff) {
  if (fbuff == NULL) {
    SOFT_EXIT("rb_resize", NULL_PARAM);
  }
  uint8_t *newBuff = (uint8_t*) calloc(1, sizeof(uint8_t));
  if (newBuff == NULL) {
    SOFT_EXIT("rb_resize", NULL_AFTER_CREATION);
  }
  free(fbuff->buffer);
  fbuff->buffer = newBuff;
  fbuff->size = 1;
  fbuff->end = 0;
}
void fb_resize(fbuff *fbuff, uint64_t size) {
  if (fbuff == NULL) {
    SOFT_EXIT("rb_resize", NULL_PARAM);
  }
  fbuff->buffer = (uint8_t*)realloc(fbuff->buffer, (size) * sizeof(uint8_t));
  fbuff->size = size;
  fbuff->end = size-1;
}
