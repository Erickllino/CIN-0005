#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class player {
private:



    
public:
    player(int x, int y, int radius);
    int radius = 10;
    int x, y;
    int vx, vy;
    void draw();
    void move();
    void change_vx(int dx);
    void change_vy(int dy);
};

#endif
