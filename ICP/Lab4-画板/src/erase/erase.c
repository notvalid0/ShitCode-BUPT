#include "erase.h"
#include "raylib.h"

void eraser(int *colorUsed, int *prevColor) {
  if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
    *prevColor = *colorUsed;
  }
  if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    *colorUsed = 10;
  }
  if (IsMouseButtonReleased(MOUSE_RIGHT_BUTTON)) {
    *colorUsed = *prevColor;
  }
}