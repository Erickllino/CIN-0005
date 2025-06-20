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

  while (!WindowShouldClose()) {
    
    game.play_step(p);

    // Check for exit key (Escape)
    if (IsKeyPressed(KEY_ESCAPE)) {
      break;
    }


  }
  CloseWindow();
  return 0;
}
