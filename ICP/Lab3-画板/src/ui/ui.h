#pragma once
#include "raylib.h"

extern Color colors[11];
extern Rectangle chooseColor[10];

void initToolbar(void);
void drawToolbar(int colorUsed, Vector2 mousePos);
void handleEraser(int* colorUsed, int* prevColor);
