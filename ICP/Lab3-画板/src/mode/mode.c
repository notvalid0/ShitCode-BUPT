#include "mode.h"
#include <raylib.h>

void switchMode(int *mode, bool *showPolyHint) {
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
        *showPolyHint = true;
        *mode = 4;
    }
}

void showMode(int mode) {
    Rectangle hintRec = {500, 10, 120, 30};
            DrawRectangleLinesEx(hintRec, 2, BLACK);
    switch(mode) {
        case 0:;
            DrawText("Now In DRAW MODE", 505, 20, 10, BLACK);
            break;
        case 1:;
            DrawText("Now In Line MODE", 505, 20, 10, BLACK);
            break;
        case 2:;
            DrawText("Now In Triangle MODE", 505, 20, 6, BLACK);
            break;
        case 3:;
            DrawText("Now In Square MODE", 505, 20, 8, BLACK);
            break;
        case 4:;
            DrawText("Now In Polygon MODE", 505, 20, 6, BLACK);
            break;
        default:;
            break;
    }
}