#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "raylib.h"
#include <vector>
#include <utility>
#include <iostream>
#include <cmath>
#include <unordered_map>

using std::vector;
using std::pair;

#define CODE_SIZE 101

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
    
    Sound ball_collision = LoadSound("assets/sounds/collision.wav");

    vector<pair<Vector2, Vector2>> walls ;
    vector<pair<Vector2, Vector2>> p_walls;
    void play_step(player &p, char fase_atual[CODE_SIZE]);

    GameState menu(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState continue_menu(GameState game_state, char fase[CODE_SIZE], player &p);

};


#endif /* GAME_H */
