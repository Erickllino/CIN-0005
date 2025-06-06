#include "game.h"
#include <raylib.h>
#include <iostream>
#include <cmath>

// Inicializa o jogo com paredes de borda e paredes internas
Game::Game(float width, float height) {
    screenWidth = width;
    screenHeight = height;

    // Paredes externas
    walls = {
        {{0, 0}, {screenWidth, 0}},                    // Topo
        {{screenWidth, 0}, {screenWidth, screenHeight}},  // Direita
        {{screenWidth, screenHeight}, {0, screenHeight}},  // Fundo
        {{0, screenHeight}, {0, 0}}                    // Esquerda
    };

    // Obstáculo interno (exemplo)
    p1_walls = {
        {{300, 100}, {400, 100}},
        {{400, 100}, {400, 200}},
        {{400, 200}, {300, 200}},
        {{300, 200}, {300, 100}}
    };

    walls.insert(walls.end(), p1_walls.begin(), p1_walls.end());
}

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

// Função principal de jogo
void Game::play_step(player &p) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Input
    if (IsKeyDown(KEY_UP))    p.acelerate_y(-0.1f);
    if (IsKeyDown(KEY_DOWN))  p.acelerate_y(0.1f);
    if (IsKeyDown(KEY_LEFT))  p.acelerate_x(-0.1f);
    if (IsKeyDown(KEY_RIGHT)) p.acelerate_x(0.1f);
    if (IsKeyDown(KEY_SPACE)) {
        float breakForce = 0.05;
        p.vx -= p.vx * breakForce;
        p.vy -= p.vy * breakForce;
    }
    // Desenha obstáculos
    for (auto &seg : p1_walls) {
        DrawLineV(seg.first, seg.second, RED);
    }

    // Atualiza posição
    Vector2 pos = {p.x, p.y};
    Vector2 vel = {p.vx, p.vy};
    float r = p.radius;

    // Verifica colisão com paredes
    for (auto &seg : walls) {
        Vector2 cp, normal;
        if (CheckCollisionCircleLine(pos, r, seg.first, seg.second, cp, normal)) {
            float dot = Dot(vel, normal);
            vel = Sub(vel, Scale(normal, 2 * dot));
            pos = Add(cp, Scale(normal, r));
            break;
        }
    }

    // Verifica bordas da tela para evitar sair da tela mesmo com colisão
    if (pos.x - r < 0) {
        pos.x = r;
        vel.x *= -1;
    }
    if (pos.x + r > screenWidth) {
        pos.x = screenWidth - r;
        vel.x *= -1;
    }
    if (pos.y - r < 0) {
        pos.y = r;
        vel.y *= -1;
    }
    if (pos.y + r > screenHeight) {
        pos.y = screenHeight - r;
        vel.y *= -1;
    }

    // Aplica nova posição e velocidade ao player
    p.x = pos.x;
    p.y = pos.y;
    // Limita a velocidade
    vel.x = Clamp(vel.x, -5.0f, 5.0f);
    vel.y = Clamp(vel.y, -5.0f, 5.0f);
    p.vx = vel.x;
    p.vy = vel.y;

    p.move();   // atualiza a posição com a velocidade
    p.draw();   // desenha o jogador

    EndDrawing();
}
