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
    Texture2D menu_fundo;
    Texture2D select_fundo;
    Texture2D score_fundo;
    Texture2D bordastart;
    Texture2D bordasel;
    Texture2D bordacredits;

    Texture2D base_support; // Textura para o suporte da bola
    Texture2D erick_card;
    Texture2D heitor_card;
    Texture2D ivan_card;
    Texture2D jess_card;
    Texture2D leball_card;
    Texture2D sami_card;


	int frame;
	float timer;
	float frameDuration;

    bool leBallActive; // Flag para verificar se LeBall está ativo
    float leBallTimer; // Tempo que LeBall está ativo
    float leBallCooldown;

    Sound bumperSound; // Som do bumper
    Music gameMusic; // Música do jogo
    bool musicLoaded; // Flag para verificar se a música foi carregada

public:
    Game(float screenWidth, float screenHeight);
	~Game(); //descarrega textura
    
    float screenWidth = 800;
    float screenHeight = 600;

    enum GameState {
        MENU,
        CHARACTER_SELECTION,
        PLAYING,
		CINEMATIC,
        SCOREBOARD,
        PAUSED,
        YOU_WIN,
        GAME_OVER,
        CONTINUE_MENU,
        CREDITS
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

    // Variáveis para controle de tempo e habilidades especiais
    float playTimer;
    float buttonPressTime;

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
    void restartMusic(); // Método para reiniciar a música
    GameState selectCharacter(GameState game_state, char fase[CODE_SIZE], player &p);

    GameState credits(GameState game_state, char fase[CODE_SIZE], player &p);

};


#endif /* GAME_H */
