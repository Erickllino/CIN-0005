#ifndef BUMPER_H
#define BUMPER_H

#include "raylib.h"

class Bumper {
public:
    Vector2 position;
    float radius;
    float originalRadius; // Para o efeito de pulsação
    Color color;
    bool isHit;
    float hitTimer; // Tempo para o efeito de pulsação
    int scoreValue; // pontuacao do bumper

    Bumper(Vector2 pos, float r, Color c, int score);
    void draw();
    void update(float dt); // dt = delta time para animação
    bool checkCollision(const Vector2& ballPos, float ballRadius, Vector2& normal, float& penetration);
    void onHit(); // O que acontece quando o bumper é atingido
};

#endif