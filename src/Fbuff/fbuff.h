#pragma once

#include "../rerror.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct {
  uint8_t *buffer;
  uint64_t size;
  uint64_t end;
} fbuff;

void fb_init(fbuff* fbuff);
void fb_pushback(fbuff *fbuff, uint8_t item);
void fb_clear(fbuff *fbuff, uint8_t item);
void fb_reset(fbuff *fbuff);
void fb_resize(fbuff *fbuff, uint64_t size);
