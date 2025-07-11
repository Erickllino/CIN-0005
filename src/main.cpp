#include "raylib.h"
#include "player.h"
#include "game.h"

float screenWidth = 800.0;
float screenHeight = 600.0;


int main() {
  // Initialize the window
  InitWindow(screenWidth, screenHeight, "raylib basic window");
  SetTargetFPS(120);
  Game game(screenWidth, screenHeight);
  player p((float) screenWidth/2,(float) screenHeight/2, 10);
  Game::GameState game_state = Game::MENU;
  
  while (!WindowShouldClose()) {

    // Open menu
    char fase[CODE_SIZE] = "fase1"; // Fase inicial
    game_state = game.menu(game_state);
    
    while(game_state == Game::PLAYING) {
      game.play_step(p, fase);
      if (IsKeyPressed(KEY_ESCAPE)) {
        break;
      }
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
      break;
    }

    // Check for exit key (Escape)



  }
  CloseWindow();
  return 0;
}
