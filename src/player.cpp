#include "player.h"
#include <raylib.h>

player::player(int x, int y, int radius)
    : x(x), y(y), radius(radius), vx(0), vy(0) {}

void player::draw() {
    DrawCircle(x,y, radius, RED);
    
}

void player::move() {
    x += vx;
    y += vy;
}

void player::change_vx(int dx) {
    vx = dx;
}

void player::change_vy(int dy) {
    vy = dy;
}
