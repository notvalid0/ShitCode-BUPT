#include "shape.h"
#include <raylib.h>

#define MAX_SHAPE 100

lineShape lines[MAX_SHAPE];
triangleShape triangles[MAX_SHAPE];
squareShape squares[MAX_SHAPE];
polyShape polys[MAX_SHAPE];
shapeIndex shapes[5 * MAX_SHAPE];

static int lineCount = 0;
static int triangleCount = 0;
static int squareCount = 0;
static int polyCount = 0;
static int indexCount = 0;

void storeLine(lineShape line) {
  if (lineCount < MAX_SHAPE) {
    lines[lineCount] = line;
    shapes[indexCount].mode = 1;
    shapes[indexCount++].num = lineCount;
    lineCount++;
  }
}
void storeTriangle(triangleShape triangle) {
  if (triangleCount < MAX_SHAPE) {
    triangles[triangleCount] = triangle;
    shapes[indexCount].mode = 2;
    shapes[indexCount++].num = triangleCount;
    triangleCount++;
  }
}
void storeSquare(squareShape square) {
  if (squareCount < MAX_SHAPE) {
    squares[squareCount] = square;
    shapes[indexCount].mode = 3;
    shapes[indexCount++].num = squareCount;
    squareCount++;
  }
}
void storePoly(polyShape poly) {
  if (polyCount < MAX_SHAPE) {
    polys[polyCount] = poly;
    shapes[indexCount].mode = 4;
    shapes[indexCount++].num = polyCount;
    polyCount++;
  }
}

void drawLineShape(int i) {
  DrawCircle(lines[i].startPoint.x, lines[i].startPoint.y, lines[i].radius,
             lines[i].color);
  DrawLineEx(lines[i].startPoint, lines[i].endPoint, 2 * lines[i].radius,
             lines[i].color);
  DrawCircle(lines[i].endPoint.x, lines[i].endPoint.y, lines[i].radius,
             lines[i].color);
}

void drawTriangleShape(int i) {
  for (int j = 0; j < 2; j++)
    DrawTriangle(triangles[i].point1[j], triangles[i].point2[j],
                 triangles[i].point3[j], triangles[i].color);
}

void drawSquareShape(int i) {

  int squarewidth = (int)squares[i].point2.x - (int)squares[i].point1.x;
  int squareheight = (int)squares[i].point2.y - (int)squares[i].point1.y;
  DrawRectangle(squares[i].point1.x, squares[i].point1.y, squarewidth,
                squareheight, squares[i].color);
}

void drawPolyShape(int i) {
  DrawPoly(polys[i].center, polys[i].sides, polys[i].radius, polys[i].rotation,
           polys[i].color);
}

void drawAllShapes() {
  for (int i = 0; i < indexCount; i++) {
    if (shapes[i].mode == 1)
      drawLineShape(shapes[i].num);
    else if (shapes[i].mode == 2)
      drawTriangleShape(shapes[i].num);
    else if (shapes[i].mode == 3)
      drawSquareShape(shapes[i].num);
    else if (shapes[i].mode == 4)
      drawPolyShape(shapes[i].num);
  }
}

void clearShapes() {
  lineCount = 0;
  triangleCount = 0;
  squareCount = 0;
  polyCount = 0;
  indexCount = 0;
}

// 切换Shape模式All in one
void shapeErase() {
  if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
    if (IsKeyPressed(KEY_Z)) {
      if (indexCount > 0) {
        indexCount--;
        switch (shapes[indexCount].mode) {
        case 1:
          lineCount--;
          break;
        case 2:
          triangleCount--;
          break;
        case 3:
          squareCount--;
          break;
        case 4:
          polyCount--;
          break;
        default:
          break;
        }
      }
    }
  }
}
