#include "canvas.h"
#include "windows.h"
#include "../Shapes/shape.h"

void initCanvas(RenderTexture2D* canvas) {
    *canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    BeginTextureMode(*canvas);
    ClearBackground(RAYWHITE);
    EndTextureMode();
}

void clearCanvas(RenderTexture2D* canvas) {
    BeginTextureMode(*canvas);
    ClearBackground(RAYWHITE);
    clearShapes(); //来自shape.c
    EndTextureMode();
}

void drawCanvas(RenderTexture2D* canvas, Vector2* previousMousePos, bool* isFirstDraw, 
                   Vector2 mousePos, float brushSize, Color color) {
    BeginTextureMode(*canvas);
    if (*isFirstDraw) {
        DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, color);
        *isFirstDraw = false;
    } else {
        DrawLineEx(*previousMousePos, mousePos, brushSize * 2, color);
    }
    DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, color);
    EndTextureMode();
    *previousMousePos = mousePos;
}
