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

#define CODE_SIZE 100

class Game {
private:

public:
    Game(float screenWidth, float screenHeight);
    
    float screenWidth = 800;
    float screenHeight = 600;

    enum GameState {
        MENU,
        PLAYING,
        PAUSED,
        GAME_OVER,
        CONTINUE_MENU
    };

    vector<pair<Vector2, Vector2>> walls ;
    vector<pair<Vector2, Vector2>> p1_walls;
    void play_step(player &p, char fase_atual[CODE_SIZE]);

    GameState menu(GameState game_state);
    GameState continue_menu(GameState game_state);

};


#endif /* GAME_H */
