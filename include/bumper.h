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

    Bumper(const Bumper& other); //constructor de cópia
    Bumper& operator=(const Bumper& other); // operador de atribuição
    Bumper();


    Bumper(Vector2 pos, float r, Color c);
    void draw();
    void update(float dt); // dt = delta time para animação
    bool checkCollision(const Vector2& ballPos, float ballRadius, Vector2& normal, float& penetration);
    void onHit(); // O que acontece quando o bumper é atingido
};

#endif