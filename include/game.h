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
        CHARACTER_SELECTION,
        PLAYING,
        SCOREBOARD,
        PAUSED,
        GAME_OVER,
        CONTINUE_MENU
    };
    
    std::vector<player> balls;
    Vector2 initialBallPos = {100, 500};

    Sound ball_collision = LoadSound("assets/sounds/collision.wav");

    // Variáveis para os flipers
    Vector2 leftFlipperPos;
    Vector2 rightFlipperPos;
    float leftFlipperAngle;
    float rightFlipperAngle;
    float flipperLength;
    bool leftFlipperPressed;
    bool rightFlipperPressed;

    vector<pair<Vector2, Vector2>> walls ;
    vector<pair<Vector2, Vector2>> p_walls;
    GameState play_step(GameState game_state, char fase[CODE_SIZE]);

    GameState menu(GameState game_state, char fase[CODE_SIZE]);
    GameState continue_menu(GameState game_state, char fase[CODE_SIZE]);
    GameState selectCharacter(GameState game_state, char fase[CODE_SIZE]);

};


#endif /* GAME_H */
