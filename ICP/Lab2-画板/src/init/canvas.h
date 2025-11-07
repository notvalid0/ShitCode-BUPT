#pragma once
#include "raylib.h"

void initCanvas(RenderTexture2D* canvas);
void clearCanvas(RenderTexture2D* canvas);
void drawCanvas(RenderTexture2D* canvas, Vector2* previousMousePos, bool* isFirstDraw, 
                   Vector2 mousePos, float brushSize, Color color);
