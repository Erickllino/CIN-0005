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
  int paused = 0;
  while (!WindowShouldClose()) {

    // Open menu
    char fase[CODE_SIZE] = "fase1"; // Fase inicial
    
    switch (game_state) {
      case Game::MENU:
        game_state = game.menu(game_state);
        break;
      case Game::PLAYING:
        game.play_step(p, fase);
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
        game_state = game.continue_menu(game_state);
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

    // if (IsKeyPressed(KEY_ESCAPE)) {
    //   game_state = Game::GAME_OVER; // Change to game over state
    // }

    // Check for exit key (Escape)



  }
  CloseWindow();
  return 0;
}
