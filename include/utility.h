#ifndef D1AA2EEE_118B_463F_B653_6648484E0DED
#define D1AA2EEE_118B_463F_B653_6648484E0DED

#include "raylib.h"
#include <cmath>

// Declarações das funções (apenas headers)
float Dot(Vector2 a, Vector2 b);
Vector2 Sub(Vector2 a, Vector2 b);
Vector2 Add(Vector2 a, Vector2 b);
Vector2 Scale(Vector2 v, float s);
Vector2 Normalize(Vector2 v);
float Length(Vector2 v);
float Clamp(float value, float min, float max);
bool CheckCollisionCircleLine(Vector2 center, float radius, Vector2 A, Vector2 B, Vector2 &closestPoint, Vector2 &outNormal);

#endif /* D1AA2EEE_118B_463F_B653_6648484E0DED */
