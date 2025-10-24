#include "raylib.h"
#include <sys/types.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "鼠鼠画板");    //初始化canvas
    
    Color colors[11] = {BLACK, WHITE, PINK, BLUE, GREEN, YELLOW, PURPLE, RED, BROWN, YELLOW, RAYWHITE};//颜色设置(暂定10种)，颜色均来自于CHEATSHEET定义(似乎raylib.h有定义)
    
    Rectangle chooseColor[10] = {0};
    for (int i = 0; i < 10; i++){
        chooseColor[i].x = 10 + 30.0f*i + 2*i;
        chooseColor[i].y = 10;
        chooseColor[i].width = 30;
        chooseColor[i].height = 30;
    } //设定选择颜色工具栏(Cheatsheet没有找到相关文档，通过AI的帮助💦解决)

    int colorUsed = 0;
    float brushSize = 20.0f;

    RenderTexture2D mousecanvas= LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT); //渲染画布
    BeginTextureMode(mousecanvas);
    ClearBackground(RAYWHITE);
    EndTextureMode();
    SetTargetFPS(120);

    bool showSaveMessage = false;
    int saveMessageCounter = 0;

    bool startDraw = false;

    Rectangle hintRec = { 650, 10, 105, 30 };

    bool isFirstDraw = true;
    Vector2 previousMousePos = {0};

    while (!WindowShouldClose()) {  //windowshouldclose为内置函数
        Vector2 mousePos = GetMousePosition();
        if (! IsMouseButtonDown(MOUSE_RIGHT_BUTTON)){
            if (IsKeyPressed(KEY_LEFT)) {
                colorUsed--;
            }
            else if (IsKeyPressed(KEY_RIGHT)) {
                colorUsed++; //Switch Color Using left and right
            }
            if (colorUsed < 0) {
                colorUsed += 10;
            }
            else if (colorUsed >9) {
                colorUsed -= 10; 
            }//限制颜色在10种内
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            colorUsed = 10;
        }

        if (IsKeyPressed(KEY_D)){
            colorUsed = 0;
        }
        
        brushSize += GetMouseWheelMove()*5;//通过滚轮调控笔刷大小
        if (IsKeyPressed(KEY_UP)){
            brushSize += 1;
        }
        else if (IsKeyPressed(KEY_DOWN)) {
            brushSize -= 1;
        }
        if (brushSize < 2) {
            brushSize = 2;
        }
        else if (brushSize > 50) {
            brushSize = 50;
        }//限制笔刷大小

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
            BeginTextureMode(mousecanvas);
            ClearBackground(RAYWHITE);
            isFirstDraw = true;
            EndTextureMode();
        } //清楚画板内容(参考exmaple）

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            BeginTextureMode(mousecanvas);
            if (isFirstDraw) {
                // 如果是第一次绘制，只画一个圆点
                DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[colorUsed]);
                isFirstDraw = false;
            } else {
                // 否则绘制从上一个位置到当前位置的线条
                DrawLineEx(previousMousePos, mousePos, brushSize*2, colors[colorUsed]);
            }
            
            // 同时绘制当前位置的圆点，使线条末端更平滑
            DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[colorUsed]);
            
            EndTextureMode();
        } //绘画功能(第二句参考AI)，已查找Cheatsheet查证
        
        // 更新上一个鼠标位置
        previousMousePos = mousePos;

        //此部分部分选用并改进自AI协助代码
        // Image saving logic
        // NOTE: Saving painted texture to a default named image
        if (IsKeyPressed(KEY_S))
        {
            Image image = LoadImageFromTexture(mousecanvas.texture);
            ImageFlipVertical(&image);
            ExportImage(image, "my_amazing_texture_painting.png");
            UnloadImage(image);
            showSaveMessage = true;
        }

        if (showSaveMessage)
        {
            // On saving, show a full screen message for 2 seconds
            saveMessageCounter++;
            if (saveMessageCounter > 240)
            {
                showSaveMessage = false;
                saveMessageCounter = 0;
            }
        }

        //提示部分，参考自贪吃蛇example(未完成)
        if (IsKeyPressed(KEY_ENTER))
        {
            startDraw = true;
        }

        if (IsKeyPressed(KEY_H))
        {
            startDraw = false;
        }
        else if (IsKeyReleased(KEY_H))
         {
            startDraw = true;
        }

        //开始画画
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        if (!startDraw) {
            DrawText("PRESS [LEFT_MOUSE] TO DRAW\nPRESS [CTRL] + [C] TO RENEW THE CANVAS\nPRESS [RIGHT_MOUSE] TO EREASE\nPRESS [LEFT] OR [RIGHT] TO SWITCH COLOR\nPRESS [UP] AND [DOWN] TO ADJUST THE RADIUS\n           (OR USING THE MOUSE WHEEL)\nPRESS [S] TO SAVE\nPRESS [ENTER] TO START DRAWING", GetScreenWidth()/2 - MeasureText("PRESS [UP] AND [DOWN] TO ADJUST THE RADIUS", 20)/2, GetScreenHeight()/2 - 50, 20, GRAY);
        }
        else if (startDraw) {
            DrawTextureRec(mousecanvas.texture, 
                          (Rectangle){0, 0, mousecanvas.texture.width, -mousecanvas.texture.height}, 
                          (Vector2){0, 0}, 
                          WHITE);
        
            DrawCircle((int)mousePos.x, (int)mousePos.y, brushSize, colors[colorUsed]);

            // 颜色色块 （参考(贪吃蛇)EXAMPLE）
            for (int i = 0; i < 10; i++) DrawRectangleRec(chooseColor[i], colors[i]);
            DrawRectangleLines(10, 10, 30, 30, LIGHTGRAY);

            // 人性化提示方块
            DrawRectangleLinesEx(hintRec, 2,  BLACK);
            DrawText("Press H For Hints!", 655, 20, 10,  BLACK);

            // Draw save image message
            if (showSaveMessage)
            {
                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));
                DrawRectangle(0, 150, GetScreenWidth(), 80, BLACK);
                DrawText("IMAGE SAVED!", 150, 180, 20, RAYWHITE);
            }
        }


        EndDrawing();
    }
    UnloadRenderTexture(mousecanvas);
    CloseWindow();

    return 0;
}