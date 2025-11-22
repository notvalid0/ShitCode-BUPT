#pragma once
#include "raylib.h"

void drawHelpHints(void);
void drawSaveMessage(bool *showSaveMessage);
void drawLoadPrompt(bool* showLoadMessage, bool* hasSaved, RenderTexture2D canvas);
void drawSuccessMessage(bool *showSuccessMessage);
void drawPolyHint(bool *showPolyHint);