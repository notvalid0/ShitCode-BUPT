#include "startpage.h"
#include <raylib.h>

void showStartPage(void) {
    Texture2D startImage = LoadTexture("start.png");
    
    // 缩放（图片过大）
    float scale = (450.0f / startImage.height);

    // 图片居中
    int width = (int)(startImage.width * scale);
    int height = (int)(startImage.height * scale);
    int posX = (800 - width) / 2;
    int posY = (450 - height) / 2;

    // 时间控制
    float timer = 0.0f;
    float fadeInDuration = 2.0f;
    float showDuration = 1.0f;
    float fadeOutDuration = 1.0f;
    float totalDuration = fadeInDuration + showDuration + fadeOutDuration;

    while (!WindowShouldClose()) {
        timer += GetFrameTime();

        float imageAlpha = 0.0f;
        if (timer < fadeInDuration) {
            imageAlpha = timer / fadeInDuration;
        } else if (timer < fadeInDuration + showDuration) {
            imageAlpha = 1.0f;
        } else if (timer < totalDuration) {
            imageAlpha = 1.0f - (timer - fadeInDuration - showDuration) / fadeOutDuration;
        } else {
            break;
        }

        BeginDrawing();
        ClearBackground(WHITE);

        // 绘制缩放后的图片
        DrawTextureEx(
            startImage,
            (Vector2){(float)posX, (float)posY},  // 位置
            0.0f,
            scale,// 缩放
            (Color){255, 255, 255, (unsigned char)(imageAlpha * 255)}//AI提供
        );

        EndDrawing();
    }

    UnloadTexture(startImage);
}