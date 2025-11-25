#pragma once
#include "raylib.h"
#define MAX_SHAPE 100

typedef struct {
  Vector2 startPoint;
  Vector2 endPoint;
  float radius;
  Color color;
} lineShape;

typedef struct {
  Vector2 point1;
  Vector2 point2;
  Vector2 point3;
  Color color;
} triangleShape;

typedef struct {
  Vector2 point1;
  Vector2 point2;
  Color color;
} squareShape;

typedef struct {
  int point1[1];
  int point2[2];
  int lenth;
} square;

typedef struct {
  Vector2 center;
  int sides;
  float radius;
  float rotation;
  Color color;
} polyShape;

int getColorUsed();

void storeLine(lineShape line);
void storeTriangle(triangleShape triangle);
void storeSquare(squareShape square);
void storePoly(polyShape poly);

void drawAllLineShape();
void drawAllTriangleShape();
void drawAllSquareShape();
void drawAllPolyShape();

void clearShapes();
void shapeErase(int mode);