#include "raylib.h" // check

#include "game.h"


float screenWidth = 800.0;
float screenHeight = 600.0;


int main() {
  // Initialize the window
  SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "raylib basic window");
  InitAudioDevice();
  SetTargetFPS(120);
  Game game(screenWidth, screenHeight);
  player p((float) screenWidth/2,(float) screenHeight/2, 10);
  Game::GameState game_state = Game::MENU;
  int paused = 0;
  char fase[CODE_SIZE] = "\0";

  while (!WindowShouldClose()) {

    // Open menu
    
    switch (game_state) {
      case Game::MENU:
        game_state = game.menu(game_state, fase, p);
        break;
      case Game::CINEMATIC: 
        game_state = game.cinematic_step(game_state, fase, p);
        break;
      case Game::PLAYING:
        game_state = game.play_step(game_state, fase, p);
        break;
      case Game::SCOREBOARD:
        // Placeholder for scoreboard logic
        game_state = game.Scoreboard(game_state, fase, p);
        break;
      case Game::GAME_OVER:
        // Placeholder for game over logic
        DrawText("Game Over! Press ESC to exit.", screenWidth / 2 - 100, screenHeight / 2 - 20, 20, RED);
        if (IsKeyPressed(KEY_ESCAPE)) {
          CloseWindow();
          return 0; // Exit the game
        }
        break;
      case Game::CONTINUE_MENU:
        // TODO: Implement continue menu logic
        game_state = game.continue_menu(game_state, fase, p);
        break;
      case Game::PAUSED:
        BeginDrawing();
        paused--;
        DrawText("Game Paused! Press M to return to menu.", screenWidth / 2 - 100, screenHeight / 2 - 20, 20, RED);
        if (IsKeyPressed(KEY_O) && game_state == Game::PAUSED) {
          game_state = Game::PLAYING; // Resume the game
        }
        EndDrawing();
        break;
        
    }

    if (IsKeyPressed(KEY_M)) {
      game_state = Game::MENU; // Change to menu state
    }
    // TODO: Solve P double press issue
    if (IsKeyPressed(KEY_P) && game_state == Game::PLAYING && paused <= 0) {
      paused = 10; // Reset pause counter
      game_state = Game::PAUSED; // Change to paused state
    }
  }

  UnloadSound(game.ball_collision);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
