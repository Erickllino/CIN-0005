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
    {{ 152, 89 }, { 151, 311 }},
    {{ 151, 311 }, { 279, 314 }},
    {{ 279, 314 }, { 277, 291 }},
    {{ 277, 291 }, { 175, 285 }},
    {{ 175, 285 }, { 180, 114 }},
    {{ 180, 114 }, { 269, 123 }},
    {{ 269, 123 }, { 268, 89 }},
    {{ 268, 89 }, { 155, 92 }},
    {{ 348, 91 }, { 348, 91 }},
    {{ 341, 87 }, { 343, 315 }},
    {{ 343, 315 }, { 385, 311 }},
    {{ 386, 311 }, { 371, 82 }},
    {{ 371, 82 }, { 341, 84 }},
    {{ 467, 317 }, { 470, 88 }},
    {{ 470, 88 }, { 601, 294 }},
    {{ 601, 294 }, { 618, 83 }},
    {{ 619, 85 }, { 643, 85 }},
    {{ 643, 85 }, { 624, 309 }},
    {{ 624, 309 }, { 588, 308 }},
    {{ 588, 308 }, { 486, 144 }},
    {{ 486, 144 }, { 492, 312 }},
    {{ 492, 312 }, { 473, 316 }},
    {{ 473, 316 }, { 468, 315 }},
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
int i = 0;
// Função de menu (placeholder)
Game::GameState Game::menu(GameState game_state) {

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Menu Placeholder", screenWidth / 2 - 100, screenHeight / 2 - 200, 20, WHITE);
    
    // Desenha o botão "New Game"
    DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 150, 300, 50}, 0.5,0, GRAY);
    DrawText("New Game", screenWidth / 2 - 50, screenHeight / 2 - 135, 20, RED);
    
    // Desenha o botão "Continue"
    DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 50, 300, 50}, 0.5,0, GRAY);
    DrawText("Continue", screenWidth / 2 - 50, screenHeight / 2 - 35, 20, RED);

    DrawText("Press ESC to exit", screenWidth / 2 - 100, screenHeight - 20 , 20, WHITE);

    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= screenWidth / 2 - 150 && mousePos.x <= screenWidth / 2 + 150 &&
        mousePos.y >= screenHeight / 2 - 150 && mousePos.y <= screenHeight / 2 - 100) {
        
        DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 150, 300, 50}, 0.5,0, RAYWHITE);
        DrawText("New Game", screenWidth / 2 - 50 , screenHeight / 2 - 135, 20, RED);  
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return PLAYING; // Muda para o estado de jogo
        }
        
    }else if(mousePos.x >= screenWidth / 2 - 150 && mousePos.x <= screenWidth / 2 + 150 &&
        mousePos.y >= screenHeight / 2 - 50 && mousePos.y <= screenHeight / 2) {
        
        DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 50, 300, 50}, 0.5,0, RAYWHITE);
        DrawText("Continue", screenWidth / 2 - 50 , screenHeight / 2 - 35, 20, RED);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {    
            EndDrawing();  
            return CONTINUE_MENU; 
        }
        

    }else if (IsKeyPressed(KEY_ESCAPE)) {
        return GAME_OVER; // Sai do menu
    }
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo

}

Game::GameState Game::continue_menu(GameState game_state) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Continue Menu Placeholder", screenWidth / 2 - 100, screenHeight / 2 - 200, 20, WHITE);
    
    // Desenha o botão "Continue"
    DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 50, 300, 50}, 0.5,0, GRAY);
    DrawText("Continue", screenWidth / 2 - 50, screenHeight / 2 - 35, 20, RED);

    DrawText("Press ESC to exit", screenWidth / 2 - 100, screenHeight - 20 , 20, WHITE);

    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= screenWidth / 2 - 150 && mousePos.x <= screenWidth / 2 + 150 &&
        mousePos.y >= screenHeight / 2 - 50 && mousePos.y <= screenHeight / 2) {
        
        DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 50, 300, 50}, 0.5,0, RAYWHITE);
        DrawText("Continue", screenWidth / 2 - 50 , screenHeight / 2 - 35, 20, RED);  
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return PLAYING; // Muda para o estado de jogo
        }
        
    }
    
    
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        return MENU; // Sai do menu
    }
    
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo
}

// Função principal de jogo
void Game::play_step(player &p, char fase_atual[CODE_SIZE]) {
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
    // TODO: fazer com que as paredes sejam desenhadas de acordo com a fase
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
