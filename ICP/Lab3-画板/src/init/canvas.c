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
    // 将背景颜色设置为纯白色(RAYWHITE)
    ClearBackground(RAYWHITE);
    // 调用来自shape.c的clearShapes函数清除所有形状
    clearShapes(); //来自shape.c
    // 结束纹理模式
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
