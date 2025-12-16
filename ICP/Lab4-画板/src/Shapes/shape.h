#pragma once
#include "raylib.h"
#define MAX_SHAPE 100

typedef struct {
  Vector2 startPoint;
  Vector2 endPoint;
  float radius;
  Color color;
} lineShape;

// 由于官方要求必须逆时针，因此交换
typedef struct {
  Vector2 point1[2];
  Vector2 point2[2];
  Vector2 point3[2];
  Color color;
} triangleShape;

typedef struct {
  Vector2 point1;
  Vector2 point2;
  Color color;
} squareShape;

typedef struct {
  Vector2 center;
  int sides;
  float radius;
  float rotation;
  Color color;
} polyShape;

typedef struct {
  int mode; // 记录在对应
  int num;  // 记录在对应结构体内的个数
} shapeIndex;

int getColorUsed();

void storeLine(lineShape line);
void storeTriangle(triangleShape triangle);
void storeSquare(squareShape square);
void storePoly(polyShape poly);

void drawLineShape(int i);
void drawTriangleShape(int i);
void drawSquareShape(int i);
void drawPolyShape(int i);

void drawAllShapes();

void clearShapes();
void shapeErase();