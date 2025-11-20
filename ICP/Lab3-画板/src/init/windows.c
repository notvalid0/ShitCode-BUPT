#include "windows.h"
#include "raylib.h"

void initWindow(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "鼠鼠画板");
    SetTargetFPS(120);
}

void closeWindow(void) {
    CloseWindow();
}

void handleColorSwitching(int* colorUsed) {
    if (!IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
        if (IsKeyPressed(KEY_LEFT)) {
            (*colorUsed)--;
        }
        else if (IsKeyPressed(KEY_RIGHT)) {
            (*colorUsed)++;
        }
        if (*colorUsed < 0) {
            *colorUsed += 10;
        }
        else if (*colorUsed > 9) {
            *colorUsed -= 10;
        }
    }

    if (IsKeyPressed(KEY_ONE)) *colorUsed = 0;
    else if (IsKeyPressed(KEY_TWO) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 1;
    else if (IsKeyPressed(KEY_THREE) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 2;
    else if (IsKeyPressed(KEY_FOUR) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 3;
    else if (IsKeyPressed(KEY_FIVE) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 4;
    else if (IsKeyPressed(KEY_SIX) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 5;
    else if (IsKeyPressed(KEY_SEVEN) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 6;
    else if (IsKeyPressed(KEY_EIGHT) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 7;
    else if (IsKeyPressed(KEY_NINE) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 8;
    else if (IsKeyPressed(KEY_ZERO) && IsKeyDown(KEY_LEFT_CONTROL)) *colorUsed = 9;
}

void handleBrushSize(float* brushSize) {
    *brushSize += GetMouseWheelMove() * 5;
    if (IsKeyPressed(KEY_UP)) {
        *brushSize += 1;
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        *brushSize -= 1;
    }
    if (*brushSize < 2) *brushSize = 2;
    else if (*brushSize > 50) *brushSize = 50;
}
