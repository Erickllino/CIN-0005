#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class player {
private:
    // Atributos privados, se necessário   
public:
    player(float x,float y, int radius);
    int radius = 10;
    int characterId = -1; // ID do personagem selecionado
    float x, y;
    float vx, vy;
    void draw();
    void setPosition(float newX, float newY);
    void move();
    void acelerate_x(float dx);
    void acelerate_y(float dy);
};

#endif
