#include "shape.h"
#include <raylib.h>
#include "../erase/erase.h"

#define MAX_SHAPE 100

lineShape lines[MAX_SHAPE];
triangleShape triangles[MAX_SHAPE];
squareShape squares[MAX_SHAPE];
polyShape polys[MAX_SHAPE];

static int lineCount = 0;
static int triangleCount = 0;
static int squareCount = 0;
static int polyCount = 0;

void storeLine(lineShape line) {
  if (lineCount < MAX_SHAPE) lines[lineCount++] = line;
}
void storeTriangle(triangleShape triangle) {
  if (triangleCount < MAX_SHAPE) triangles[triangleCount++] = triangle;
}
void storeSquare(squareShape square) {
  if (squareCount < MAX_SHAPE) squares[squareCount++] = square;
}
void storePoly(polyShape poly) {
  if (polyCount < MAX_SHAPE) polys[polyCount++] = poly;
}

void drawAllLineShape() {
  for (int i = 0; i < lineCount; i++) {
    DrawCircle(lines[i].startPoint.x, lines[i].startPoint.y, lines[i].radius, lines[i].color);
    DrawLineEx(lines[i].startPoint, lines[i].endPoint, 2*lines[i].radius, lines[i].color);
    DrawCircle(lines[i].endPoint.x, lines[i].endPoint.y, lines[i].radius, lines[i].color);
  }
}

void drawAllTriangleShape() {
  for (int i = 0; i < triangleCount; i++) {
    DrawTriangle(triangles[i].point1, triangles[i].point2, triangles[i].point3, triangles[i].color);
  }
}

void drawAllSquareShape() {
  for (int i = 0; i < squareCount; i++) {
    int squarewidth = (int)squares[i].point2.x - (int) squares[i].point1.x;
    int squareheight = (int)squares[i].point2.y - (int) squares[i].point1.y;
    DrawRectangle(squares[i].point1.x, squares[i].point1.y, squarewidth,  squareheight, squares[i].color);
  }
}

//需要改进：目前只支持正多边形，需要读入sides数量
void drawAllPolyShape() {
  for (int i = 0; i < polyCount; i++) {
    DrawPoly(polys[i].center, polys[i].sides, polys[i].radius, polys[i].rotation, polys[i].color);  
  }
}

void clearShapes(){
  lineCount = 0;
  triangleCount = 0;
  squareCount = 0;
  polyCount = 0;
}


//切换Shape模式All in one
void shapeErase(int mode){
    if(IsKeyDown(KEY_LEFT_CONTROL)&&IsKeyPressed(KEY_Z)){
        if (mode == 1) eraseLine(&lineCount);
        else if (mode == 2) eraseTriangle(&triangleCount);
        else if (mode == 3) eraseSquare(&squareCount);
        else if (mode == 4) erasePoly(&polyCount);
    }
}
