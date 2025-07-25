#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "player.h"
#include "fases.h"
#include "utility.h"

#include <utility>
#include <iostream>
#include <cstring>

#define CODE_SIZE 101

class Game {
private:

public:
    Game(float screenWidth, float screenHeight);
    
    float screenWidth = 800;
    float screenHeight = 600;

    enum GameState {
        MENU,
        SELECT_CARACTER,
        PLAYING,
        SCOREBOARD,
        PAUSED,
        GAME_OVER,
        CONTINUE_MENU
    };
    
    Sound ball_collision = LoadSound("assets/sounds/collision.wav");

    vector<pair<Vector2, Vector2>> walls ;
    vector<pair<Vector2, Vector2>> p_walls;
    
    // Variáveis para os flipers
    Vector2 leftFlipperPos;
    Vector2 rightFlipperPos;
    float leftFlipperAngle;
    float rightFlipperAngle;
    float flipperLength;
    bool leftFlipperPressed;
    bool rightFlipperPressed;
    
    GameState play_step(GameState game_state, char fase[CODE_SIZE], player &p);

    GameState menu(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState continue_menu(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState Scoreboard(GameState game_state, char fase[CODE_SIZE], player &p);

};


#endif /* GAME_H */
