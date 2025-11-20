#include "hint.h"
#include "counter.h"

void drawHelpHints(void) {
    DrawText("PRESS [LEFT_MOUSE] TO DRAW\nPRESS [CTRL] + [C] TO RENEW THE CANVAS\nPRESS [RIGHT_MOUSE] TO EREASE\nPRESS [LEFT] OR [RIGHT] TO SWITCH COLOR\n          or use[CTRL] + [1]-[9]\nPRESS [UP] AND [DOWN] TO ADJUST THE RADIUS\n           (OR USING THE MOUSE WHEEL)\nPRESS [S] TO SAVE\nPRESS [ENTER] TO START DRAWING", 
            GetScreenWidth()/2 - MeasureText("PRESS [UP] AND [DOWN] TO ADJUST THE RADIUS", 20)/2, 
            GetScreenHeight()/2 - 85, 20, GRAY);
}

void drawSaveMessage(bool *showSaveMessage) {
    if (*showSaveMessage) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
        DrawRectangle(0, 185, GetScreenWidth(), 80, BLACK);
        DrawText("IMAGE SAVED!", (GetScreenWidth()-MeasureText("IMAGE SAVED!", 20))/2, 215, 20, RAYWHITE);
        *showSaveMessage = timeCounter();
    }
}

void drawLoadPrompt(bool* showLoadMessage, bool* hasSaved, RenderTexture2D canvas) {
    if (*hasSaved && *showLoadMessage) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
        DrawRectangle(0, 185, GetScreenWidth(), 80, BLACK);
        DrawText("Saved Work Detected, Wanna Load It? (Y/n)", 180, 215, 20, RAYWHITE);
    }
}

void drawSuccessMessage(bool *showSuccessMessage) {
    if (*showSuccessMessage) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
        DrawRectangle(0, 185, GetScreenWidth(), 80, BLACK);
        DrawText("IMAGE LOADED SUCCESSFULLY!", (GetScreenWidth()-MeasureText("IMAGE LOADED SUCCESSFULLY!", 20))/2, 215, 20, RAYWHITE);
        *showSuccessMessage = timeCounter();
    }
}