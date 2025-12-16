#include "ui.h"

Color colors[11] = {BLACK, WHITE, PINK, BLUE, GREEN, YELLOW, PURPLE, RED, BROWN, YELLOW, RAYWHITE};
Rectangle chooseColor[10] = {0};

void initToolbar(void) {
    for (int i = 0; i < 10; i++) {
        chooseColor[i].x = 10 + 30.0f * i + 2 * i;
        chooseColor[i].y = 10;
        chooseColor[i].width = 30;
        chooseColor[i].height = 30;
    }
}

void drawToolbar(int colorUsed, Vector2 mousePos) {
    for (int i = 0; i < 10; i++) {
        DrawRectangleRec(chooseColor[i], colors[i]);
    }
    DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);
}