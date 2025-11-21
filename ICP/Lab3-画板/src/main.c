#include <raylib.h>
#include <stdio.h>
#include "Shapes/shape.h"
#include "init/windows.h"
#include "init/canvas.h"
#include "ui/ui.h"
#include "hint/hint.h"
#include "startpage/startpage.h"
#include "Shapes/drawshape.h"
#include "mode/mode.h"

int main(void) {
    // 初始化窗口和画布
    initWindow();
    RenderTexture2D mousecanvas;
    initCanvas(&mousecanvas);
    initToolbar();

    // 初始化状态变量
    int colorUsed = 0;
    float brushSize = 20.0f;
    bool showSaveMessage = false;
    bool startDraw = false;
    Vector2 previousMousePos = {0};
    bool isFirstDraw = true;
    int prevColor = 0;
    bool hasSaved = false;
    bool showLoadMessage = false;
    bool showSuccessMessage = false;
    int mode = 0;
    int sides = 6; // 默认多边形边数

    //显示开始屏幕
    showStartPage();
    
    // 检查保存的文件
    FILE *f = fopen("鼠鼠作品.png", "rb");
    if (f) { 
        fclose(f); 
        hasSaved = true; 
        showLoadMessage = true;
    }

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        // 处理颜色切换
        handleColorSwitching(&colorUsed);
        
        // 处理橡皮擦模式
        handleEraser(&colorUsed, &prevColor);
        
        // 处理画笔大小        
        handleBrushSize(&brushSize);

        // 清空画布
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C)) {
            clearCanvas(&mousecanvas);
            isFirstDraw = true;
        }

        // 处理模式切换
        switchMode(&mode);

        // 绘制到 画布
        if (mode == 0) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                drawCanvas(&mousecanvas, &previousMousePos, &isFirstDraw, 
                              mousePos, brushSize, colors[colorUsed]);
            } 

            if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)|| IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) isFirstDraw = true;
        }

        // 保存图像
        if (IsKeyPressed(KEY_S)) {
            Image image = LoadImageFromTexture(mousecanvas.texture);
            ImageFlipVertical(&image);
            ExportImage(image, "鼠鼠作品.png");
            UnloadImage(image);
            showSaveMessage = true;
        }

        // 处理提示显示
        if (IsKeyPressed(KEY_ENTER)) startDraw = true;
        if (IsKeyPressed(KEY_H)) startDraw = false;
        else if (IsKeyReleased(KEY_H)) startDraw = true;

        // 开始绘制
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (!startDraw) {
            drawHelpHints();
        } else {
            DrawTextureRec(mousecanvas.texture, 
                          (Rectangle){0, 0, mousecanvas.texture.width, -mousecanvas.texture.height}, 
                          (Vector2){0, 0}, 
                          WHITE);
            
            // 绘制形状
            drawAllLineShape();
            drawAllTriangleShape();
            drawAllSquareShape();
            drawAllPolyShape();

        // 添加形状
        if (mode == 1) {
            addNewLine(colors[colorUsed], brushSize);
        }
        if (mode == 2) {
            addNewTriangle(colors[colorUsed]);
        }
        if (mode == 3) {
            addNewSquare(colors[colorUsed]);
        }
        if (mode == 4) {
            addNewPoly(colors[colorUsed], sides);
        }
            
            // 加载提示
            drawLoadPrompt(&showLoadMessage, &hasSaved, mousecanvas);
            
            // 处理加载确认
            if (IsKeyPressed(KEY_Y) && showLoadMessage) {
                showSuccessMessage = true;
                Image img = LoadImage("鼠鼠作品.png");
                BeginTextureMode(mousecanvas);
                DrawTexture(LoadTextureFromImage(img), 0, 0, RAYWHITE);
                EndTextureMode();
                UnloadImage(img);
                showLoadMessage = false;
            } else if (IsKeyPressed(KEY_N) && showLoadMessage) {
                showLoadMessage = false;
            }

            //绘制成功加载信息
            drawSuccessMessage(&showSuccessMessage);
            
            // 绘制工具栏
            drawToolbar(colorUsed, mousePos);
            
            //绘制画笔光标
            if (mode == 0 || mode == 1) 
            DrawCircle(GetMousePosition().x, GetMousePosition().y, brushSize, colors[colorUsed]);
            else if (mode == 2)
            DrawCircle(GetMousePosition().x, GetMousePosition().y, 2.5f, colors[colorUsed]) ;

            // 绘制提示框
            Rectangle hintRec = {650, 10, 105, 30};
            DrawRectangleLinesEx(hintRec, 2, BLACK);
            DrawText("Press H For Hints!", 655, 20, 10, BLACK);
            
            // 绘制保存消息
            drawSaveMessage(&showSaveMessage);

        }
        EndDrawing();
    }

    UnloadRenderTexture(mousecanvas);
    closeWindow();
    return 0;
}
