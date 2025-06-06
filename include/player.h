#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class player {
private:



    
public:
    player(float x,float y, int radius);
    int radius = 10;
    float x, y;
    float vx, vy;
    void draw();
    void move();
    void acelerate_x(float dx);
    void acelerate_y(float dy);
};

#endif
