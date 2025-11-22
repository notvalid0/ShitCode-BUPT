#include "drawshape.h"
#include "shape.h"
#include <raylib.h>
#include <stdbool.h>


//绘制直线
void addNewLine(Color color, float radius) {
    static lineShape line;          
    static bool hasStart = false;
    line.radius = radius;

    if (!hasStart && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        line.startPoint = GetMousePosition();
        line.color = color;
        hasStart = true;
    }

    if (hasStart && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        DrawCircle(line.startPoint.x, line.startPoint.y, radius, color);
        DrawLineEx(line.startPoint, mouse, 2*radius, line.color);
    }

    if (hasStart && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        line.endPoint = GetMousePosition();
        storeLine(line);
        hasStart = false;
    }
}

//绘制三角形
void addNewTriangle(Color color) {
    static triangleShape triangle;
    static int isFirstTriangle = 0;
    triangle.color = color;
    if(isFirstTriangle == 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        triangle.point1 = GetMousePosition();
        isFirstTriangle = 1;
    }
    else if(isFirstTriangle == 1) {
         DrawLineEx(triangle.point1, GetMousePosition(), 5.0f, color);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            triangle.point2 = GetMousePosition();
            isFirstTriangle = 2;
        }
    }
    else if(isFirstTriangle == 2) {
        DrawLineEx(triangle.point1, triangle.point2, 5.0f, color);
        DrawLineEx(triangle.point1, GetMousePosition(), 5.0f, color);
        DrawLineEx(triangle.point2, GetMousePosition(), 5.0f, color);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if (triangle.point3.y <= triangle.point1.y && triangle.point3.y <= triangle.point2.y) {
                triangle.point3 = triangle.point1;
                triangle.point1 = GetMousePosition();
            }
            else {
            triangle.point3 = GetMousePosition();
            }
            storeTriangle(triangle);
            isFirstTriangle = 0;
        }
    }
}

//绘制矩形
void addNewSquare(Color color) {
    static squareShape square;
    static bool isFirstRectangle = true;
    square.color = color;
    if(isFirstRectangle&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
           square.point1 = GetMousePosition();
        isFirstRectangle = false;
    }
    else if(!isFirstRectangle) {
        if ((GetMousePosition().x - square.point1.x)*(GetMousePosition().y - square.point1.y) > 0){
            DrawRectangle(square.point1.x, square.point1.y, GetMousePosition().x - square.point1.x, GetMousePosition().y - square.point1.y, color);
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            square.point2 = GetMousePosition();
            storeSquare(square);
            isFirstRectangle = true;
            }
       }
        else if ((GetMousePosition().x - square.point1.x) * (GetMousePosition().y - square.point1.y) < 0){
            DrawRectangle(GetMousePosition().x, square.point1.y, square.point1.x - GetMousePosition().x, GetMousePosition().y - square.point1.y, color);
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                square.point2.x = square.point1.x;
                square.point1.x = GetMousePosition().x;
                square.point2.y = GetMousePosition().y;
                storeSquare(square);
                isFirstRectangle = true;
            }
       
       }
    }
}

//绘制多边形
void addNewPoly(Color color) {
    static polyShape poly;
    static int isFirstPoly = true;
    static int sides = 6;
    poly.color = color;
    if(isFirstPoly && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        poly.center = GetMousePosition();
        isFirstPoly = false;
    }
    else if(!isFirstPoly) {
        DrawPoly(poly.center, chooseSides(sides), GetMousePosition().x - poly.center.x, 0, color);
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            poly.radius = GetMousePosition().x - poly.center.x;
            poly.sides = chooseSides(sides);
            storePoly(poly);
            isFirstPoly = true;   
        }
    }
}

//选择Poly对应的边数
int chooseSides(int sides) {
    if (IsKeyPressed(KEY_FIVE) && IsKeyPressed(KEY_LEFT_ALT)) sides = 5;
    if (IsKeyPressed(KEY_SIX) && IsKeyPressed(KEY_LEFT_ALT)) sides = 6;
    if (IsKeyPressed(KEY_SEVEN) && IsKeyPressed(KEY_LEFT_ALT)) sides = 7;
    if (IsKeyPressed(KEY_EIGHT) && IsKeyPressed(KEY_LEFT_ALT)) sides = 8;
    if (IsKeyPressed(KEY_NINE) && IsKeyPressed(KEY_LEFT_ALT)) sides = 9;
    return sides;
}