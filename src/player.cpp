#include "player.h"
#include <raylib.h>

player::player(float x, float y, int radius)
    : x(x), y(y), radius(radius), vx(0), vy(0) {}

void player::draw() {
    DrawCircle(x,y, radius, RED);
    
}

void player::setPosition(float newX, float newY) {
    x = newX;
    y = newY;

    vx = 0; // Reseta a velocidade ao definir uma nova posição
    vy = 0; // Reseta a velocidade ao definir uma nova posição
}

void player::move() {
    x += vx;
    y += vy;
}

void player::acelerate_x(float dx) {
    vx += dx;
}

void player::acelerate_y(float dy) {
    vy += dy;
}
