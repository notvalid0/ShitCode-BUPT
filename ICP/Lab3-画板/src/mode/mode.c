#include "mode.h"
#include <raylib.h>

void switchMode(int *mode) {
    if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_ONE)) {
        *mode = 0;
    }
    else if(IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_TWO)) {
        *mode = 1;
    }
    else if(IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_THREE)){
        *mode = 2;
    }
    else if(IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_FOUR)){
        *mode = 3;
    }
    else if(IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_FIVE)){
        *mode = 4;
    }
}