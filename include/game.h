#ifndef GAME_H
#define GAME_H
#include "raylib.h"
#include "player.h"
#include "fases.h"
#include "utility.h"
#include "bumper.h"

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

    bool leBallActive; // Flag para verificar se LeBall está ativo
    float leBallTimer; // Tempo que LeBall está ativo
    float leBallCooldown;

    Sound bumperSound; // Som do bumper

public:
    Game(float screenWidth, float screenHeight);
	~Game(); //descarrega textura
    
    float screenWidth = 800;
    float screenHeight = 600;
    float playTimer;
    float buttonPressTime;

    enum GameState {
        MENU,
        CHARACTER_SELECTION,
        PLAYING,
		CINEMATIC,
        SCOREBOARD,
        PAUSED,
        YOU_WIN,
        GAME_OVER,
        CONTINUE_MENU
    };
    
    std::vector<player> balls;
    Vector2 initialBallPos = {1000, 500};

    Sound ball_collision;
    //Sound bumpsound = LoadSound("assets/sounds/bumper.wav");

    // Variáveis para os flipers
    Vector2 leftFlipperPos;
    Vector2 rightFlipperPos;
    float leftFlipperAngle;
    float rightFlipperAngle;
    float flipperLength;
    bool leftFlipperPressed;
    bool rightFlipperPressed;

    // Variáveis para o lançador (plunger)
    Vector2 plungerPos;
    float plungerWidth;
    float plungerHeight;
    float plungerMaxPower;
    float plungerCurrentPower;
    bool plungerCharging;
    bool ballInLauncher;
    Vector2 launcherAreaPos;
    float launcherAreaWidth;
    
    // Variáveis para controle de velocidade após lançamento
    float timeSinceLaunch;
    bool ballWasLaunched;

    vector<pair<Vector2, Vector2>> walls ;
    vector<pair<Vector2, Vector2>> p_walls;
    GameState play_step(GameState game_state, char fase[CODE_SIZE], player &p);

    std::vector<Bumper> bumpers; 

    GameState menu(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState continue_menu(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState Scoreboard(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState win_screen(GameState game_state, char fase[CODE_SIZE], player &p);
    GameState game_over_screen(GameState game_state, char fase[CODE_SIZE], player &p);
	GameState cinematic_step(GameState game_state, char fase[CODE_SIZE], player &p);
    void loadPhase(const GamePhase& phase, player& p);
    GameState selectCharacter(GameState game_state, char fase[CODE_SIZE], player &p);

};


#endif /* GAME_H */
