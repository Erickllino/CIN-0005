#include "utility.h"

// Produto escalar
float Dot(Vector2 a, Vector2 b) {
    return a.x * b.x + a.y * b.y;
}

// Subtrai dois vetores
Vector2 Sub(Vector2 a, Vector2 b) {
    return {a.x - b.x, a.y - b.y};
}

// Soma dois vetores
Vector2 Add(Vector2 a, Vector2 b) {
    return {a.x + b.x, a.y + b.y};
}

// Multiplica vetor por escalar
Vector2 Scale(Vector2 v, float s) {
    return {v.x * s, v.y * s};
}

// Normaliza vetor
Vector2 Normalize(Vector2 v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    if (len == 0) return {0, 0};
    return {v.x / len, v.y / len};
}

// Comprimento de vetor
float Length(Vector2 v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

// Clamp
float Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Verifica colisão entre círculo e segmento de reta
bool CheckCollisionCircleLine(Vector2 center, float radius,
                              Vector2 A, Vector2 B,
                              Vector2 &closestPoint, Vector2 &outNormal) {
    Vector2 AB = Sub(B, A);
    Vector2 AC = Sub(center, A);
    float t = Clamp(Dot(AC, AB) / Dot(AB, AB), 0.0f, 1.0f);
    closestPoint = Add(A, Scale(AB, t));
    Vector2 diff = Sub(center, closestPoint);
    float dist = Length(diff);
    if (dist < radius) {
        outNormal = Normalize(diff);
        return true;
    }
    return false;
}
