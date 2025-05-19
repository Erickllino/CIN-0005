#include "game.h"
#include <raylib.h>

//Game::screenWidth = 800;
//Game::screenHeight = 600;

Game::Game(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    walls = {
        {{   -1 ,    0}, {screenWidth + 1,    0}},
        {{screenWidth,    -1}, {screenWidth, screenHeight+1}},
        {{screenWidth + 1, screenHeight}, {   -1 , screenHeight}},
        {{   0, screenHeight + 1}, {   0,    -1}}
    };
    
    p1_walls = {
        {{ 300, 100}, {400, 100}},
        {{400, 100}, {400, 200}},
        {{400, 200}, {300, 200}},
        {{300, 200}, {300, 100}}
    };
}


void Game::play_step(player &p) {
    // Update the game state
    BeginDrawing();
    ClearBackground(BLACK);

    
    // Handle input
    int key = GetKeyPressed();
    if (IsKeyDown(KEY_UP))    p.change_vy(-5);  // :contentReference[oaicite:0]{index=0}
    if (IsKeyDown(KEY_DOWN))  p.change_vy(5);  // :contentReference[oaicite:1]{index=1}
    if (IsKeyDown(KEY_LEFT))  p.change_vx(-5);  // :contentReference[oaicite:2]{index=2}
    if (IsKeyDown(KEY_RIGHT)) p.change_vy(5); 

    
    // Draw the phase walls
    for (auto &seg: p1_walls) {
        Vector2 start = seg.first;
        Vector2 end   = seg.second;
        DrawLineV(start, end, RED);
    }

    walls.push_back(p1_walls[0]);
    walls.push_back(p1_walls[1]);
    walls.push_back(p1_walls[2]);
    walls.push_back(p1_walls[3]);

    // Draw the player
    p.draw();
    std::cout << "Player position: (" << p.x << ", " << p.y << ")" << std::endl;

    // Define the screen walls as line segments
    vector<pair<Vector2, Vector2>> fase_walls = walls;

    // Current velocity
    Vector2 velocity = { p.vx, p.vy };

    for (auto &seg : fase_walls) {
        Vector2 start = seg.first;
        Vector2 end   = seg.second;

        // Check for collision with the wall line
        if (CheckCollisionCircleLine({p.x, p.y}, p.radius, start, end)) {
            // Compute wall tangent and normal
            Vector2 wallDir = { end.x - start.x, end.y - start.y };
            float len = sqrt(wallDir.x*wallDir.x + wallDir.y*wallDir.y);
            Vector2 tangent = { wallDir.x/len, wallDir.y/len };
            // Normal pointing "outwards"
            Vector2 normal  = { -tangent.y, tangent.x };

            // Reflect velocity: v' = v - 2*(v·n)*n
            float dotVN = velocity.x*normal.x + velocity.y*normal.y;
            Vector2 reflected = {
                velocity.x - 2*dotVN*normal.x,
                velocity.y - 2*dotVN*normal.y
            };

            // Update player velocity
            p.vx = reflected.x;
            p.vy = reflected.y;

            // Move the player out of collision
            p.move();

            // Only handle first collision
            break;
        }
    }

    // If no collision, move normally
    p.move();

    EndDrawing();
}
