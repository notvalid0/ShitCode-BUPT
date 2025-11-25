#include "erase.h"
#include "raylib.h"

void eraser(int* colorUsed, int* prevColor) {
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

//清除lines[]中最近的线段
void eraseLine(int *lineCount){
    (*lineCount) --;
}
void eraseTriangle(int *triangleCount){
    (*triangleCount) --;
}
void eraseSquare(int *squareCount){
    (*squareCount) --;
}
void erasePoly(int *polyCount){
    (*polyCount) --;
}