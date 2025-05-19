#include "raylib.h"
#include "player.h"
#include "game.h"

int screenWidth = 800;
int screenHeight = 600;


int main() {
  // Initialize the window
  InitWindow(screenWidth, screenHeight, "raylib basic window");
  SetTargetFPS(120);
  Game game(screenWidth, screenHeight);
  player p(screenWidth/2, screenHeight/2, 10);

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
