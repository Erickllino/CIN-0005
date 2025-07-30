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
	//texturas para dar load 
	Texture2D alienship;
	Texture2D alienPinball;
	Texture2D pinballBall;

	int frame;
	float timer;
	float frameDuration;

    //Music cinematicMusic;

public:
    Game(float screenWidth, float screenHeight);
	~Game(); //descarrega textura
    
    float screenWidth = 800;
    float screenHeight = 600;

    enum GameState {
        MENU,
        SELECT_CARACTER,
        PLAYING,
		CINEMATIC,
        SCOREBOARD,
        PAUSED,
        GAME_OVER,
        CONTINUE_MENU
    };
    
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
    GameState play_step(GameState game_state, char fase[CODE_SIZE], player &p);

    GameState menu(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState continue_menu(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState Scoreboard(GameState game_state, char fase[CODE_SIZE], player &p);
	GameState cinematic_step(GameState game_state, char fase[CODE_SIZE], player &p);

};


#endif /* GAME_H */
