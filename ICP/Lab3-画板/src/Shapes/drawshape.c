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
    triangleShape triangle;
    static int isFirstTriangle = 0;
    triangle.color = color;
    if(isFirstTriangle == 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        triangle.point1 = GetMousePosition();
        isFirstTriangle = 1;
    }
    if(isFirstTriangle == 1&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        triangle.point2 = GetMousePosition();
        isFirstTriangle = 2;
    }
    if(isFirstTriangle == 2&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        triangle.point3 = GetMousePosition();
        storeTriangle(triangle);
        isFirstTriangle = 0;
    }
}

//绘制矩形
void addNewSquare(Color color) {
    squareShape square;
    static bool isFirstRectangle = true;
    square.color = color;
    if(isFirstRectangle&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        square.point1 = GetMousePosition();
        isFirstRectangle = false;
    }
    if(!isFirstRectangle&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        square.point2 = GetMousePosition();
        storeSquare(square);
        isFirstRectangle = true;
    }
}

//绘制多边形
void addNewPoly(Color color, int sides) {
    polyShape poly;
    static int isFirstPoly = true;
    poly.sides = sides;
    poly.color = color;
    if(isFirstPoly && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        poly.center = GetMousePosition();
        isFirstPoly = false;
    }
    if(!isFirstPoly && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        poly.radius = GetMousePosition().x - poly.center.x;
        storePoly(poly);
        isFirstPoly = true;
    }
}