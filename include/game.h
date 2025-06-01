#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "raylib.h"
#include <vector>
#include <utility>
#include <iostream>
#include <cmath>

using std::vector;
using std::pair;

class Game {
private:

public:
    Game(float screenWidth, float screenHeight);
    
    float screenWidth = 800;
    float screenHeight = 600;

    vector<pair<Vector2, Vector2>> walls ;
    vector<pair<Vector2, Vector2>> p1_walls;
    void play_step(player &p);


};



#endif /* GAME_H */
