#include "game.h"

// Inicializa o jogo com paredes de borda e paredes internas
Game::Game(float width, float height) {
    screenWidth = width;
    screenHeight = height;

    // Paredes externas
    walls = {
        {{0, 0}, {screenWidth, 0}},                    // Topo
        {{screenWidth, 0}, {screenWidth, screenHeight}},  // Direita
        {{screenWidth, screenHeight}, {0, screenHeight}},  // Fundo
        {{0, screenHeight}, {0, 0}}                    // Esquerda
    };
}

// Função de menu (placeholder)
Game::GameState Game::menu(GameState game_state, char fase[CODE_SIZE]) {

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Menu Placeholder", screenWidth / 2 - 100, screenHeight / 2 - 200, 20, WHITE);
    
    // Desenha o botão "New Game"
    DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 150, 300, 50}, 0.5,0, GRAY);
    DrawText("New Game", screenWidth / 2 - 50, screenHeight / 2 - 135, 20, RED);
    
    // Desenha o botão "Continue"
    DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 50, 300, 50}, 0.5,0, GRAY);
    DrawText("Continue", screenWidth / 2 - 50, screenHeight / 2 - 35, 20, RED);

    DrawText("Press ESC to exit", screenWidth / 2 - 100, screenHeight - 20 , 20, WHITE);

    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= screenWidth / 2 - 150 && mousePos.x <= screenWidth / 2 + 150 &&
        mousePos.y >= screenHeight / 2 - 150 && mousePos.y <= screenHeight / 2 - 100) {
        
        DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 150, 300, 50}, 0.5,0, RAYWHITE);
        DrawText("New Game", screenWidth / 2 - 50 , screenHeight / 2 - 135, 20, RED);  
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            strcpy(fase, "fase1");
            p_walls = p1_walls;
            walls.insert(walls.end(), p_walls.begin(), p_walls.end());
            balls.clear();
            player mainBall(initialBallPos.x, initialBallPos.y, 10);
            balls.push_back(mainBall);
            return CHARACTER_SELECTION; // Muda para o estado de jogo
        }
        
    }else if(mousePos.x >= screenWidth / 2 - 150 && mousePos.x <= screenWidth / 2 + 150 &&
        mousePos.y >= screenHeight / 2 - 50 && mousePos.y <= screenHeight / 2) {
        
        DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 50, 300, 50}, 0.5,0, RAYWHITE);
        DrawText("Continue", screenWidth / 2 - 50 , screenHeight / 2 - 35, 20, RED);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {    
            EndDrawing();  
            return CHARACTER_SELECTION;; 
        }
        

    }else if (IsKeyPressed(KEY_ESCAPE)) {
        return GAME_OVER; // Sai do menu
    }
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo

}

Game::GameState Game::selectCharacter(GameState game_state, char fase[CODE_SIZE]) {
    static int selectedCharacter = -1;
    const int numCharacters = 6;

    const char* characterNames[] = {
        "Eitor (JoaoPintoBall)",
        "Jessica (Jessball)",
        "Heiji (LeBall)",
        "Erick",
        "Samira",
        "Ivan"
    };

    const char* characterPowers[] = {
        "- Controla Ball: controla a bola levemente",
        "- Score Ball: pontuação 2x",
        "- Trava Ball: protege para a bola não cair",
        "- Slash Ball: causa dano ao redor",
        "- Vamp Ball: recupera vida com impacto",
        "- Duet Ball: invoca outras bolas (máx 4)"
    };

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Selecione seu personagem", screenWidth / 2 - 150, 50, 20, WHITE);

    Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < numCharacters; i++) {
        Rectangle btn = { screenWidth / 2 - 200, 100 + i * 70, 400, 50 };
        bool hovered = CheckCollisionPointRec(mousePos, btn);

        DrawRectangleRounded(btn, 0.3, 0, hovered ? RAYWHITE : DARKGRAY);
        DrawText(characterNames[i], btn.x + 10, btn.y + 10, 20, RED);
        DrawText(characterPowers[i], btn.x + 220, btn.y + 10, 16, WHITE);

        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedCharacter = i;

            // Aqui você pode usar selectedCharacter para definir o personagem no player p

            strcpy(fase, "fase1");
            p_walls = p1_walls;
            walls.insert(walls.end(), p_walls.begin(), p_walls.end());
            balls.clear();
            player mainBall(initialBallPos.x, initialBallPos.y, 10);
            mainBall.characterId = selectedCharacter;
            balls.push_back(mainBall);

            EndDrawing();
            return PLAYING;
        }
    }

    DrawText("Press ESC to voltar", screenWidth / 2 - 100, screenHeight - 30, 20, WHITE);

    if (IsKeyPressed(KEY_ESCAPE)) {
        EndDrawing();
        return MENU;
    }

    EndDrawing();
    return game_state;
}

Game::GameState Game::continue_menu(GameState game_state, char fase[CODE_SIZE]) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Digite o codigo da fase", screenWidth / 2 - 125, screenHeight / 2 - 200, 20, WHITE);
    
    int key = GetCharPressed();
    
    int letterCount = strlen(fase); // Tamanho máximo do código

    std::cout  << "Codigo fase: " << fase <<  " Letter count: " << letterCount <<std::endl;
    
    while (key > 0){
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < CODE_SIZE - 1))
        {
            std::cout << "Key add: " << (char)key << std::endl;
            fase[letterCount] = (char)key;
            fase[letterCount+1] = '\0'; // Add null terminator at the end of the string.
            //letterCount++;
        }
        key = GetCharPressed();  
    }

    if (IsKeyPressed(KEY_BACKSPACE)){
        if (letterCount < 0) letterCount = 0;
        fase[letterCount - 1] = '\0';
    }

    DrawText(fase, screenWidth / 2 - 100, screenHeight / 2 - 150, 20, WHITE);


    // Desenha o botão "Continue"
    DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 + 200, 300, 50}, 0.5,0, GRAY);
    DrawText("Play!", screenWidth / 2 - 25, screenHeight / 2 + 215, 20, RED);

    DrawText("Press ESC to exit", screenWidth / 2 - 100, screenHeight - 20 , 20, WHITE);

    Vector2 mousePos = GetMousePosition();
    if (mousePos.x >= screenWidth / 2 - 150 && mousePos.x <= screenWidth / 2 + 150 &&
        mousePos.y >= screenHeight / 2 + 200 && mousePos.y <= screenHeight / 2 + 250) {
        
        DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 + 200, 300, 50}, 0.5,0, RAYWHITE);
        DrawText("Play!", screenWidth / 2 - 25 , screenHeight / 2 + 215, 20, RED);  
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Define as paredes e posição inicial do jogador de acordo com a fase
            if(strcmp(fase, "") == 0) {
                strcpy(fase, "fase1");
            } else if (strcmp(fase, "fase1") == 0) {
                p_walls = p1_walls;
                walls.insert(walls.end(), p_walls.begin(), p_walls.end());
                balls.clear();
                player mainBall(initialBallPos.x, initialBallPos.y, 10);
                balls.push_back(mainBall);
            } else if (strcmp(fase, "fase2") == 0) {
                p_walls = p2_walls;
                walls.insert(walls.end(), p_walls.begin(), p_walls.end());
                balls.clear();
                player mainBall(initialBallPos.x, initialBallPos.y, 10);
                balls.push_back(mainBall);
            } else {
                std::cout << "Fase desconhecida: " << fase << std::endl;
            }
            return PLAYING; // Muda para o estado de jogo
        }
        
    }
    
    
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        return MENU; // Sai do menu
    }
    
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo
}

// Função principal de jogo
void Game::play_step(char fase[CODE_SIZE]) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (balls.empty()) { // verifica se há bolas
        EndDrawing();
        return;
    }

    player& mainBall = balls[0];

    // Começando a colocar os poderes aqui, já que a bola era controlada aqui
    if (mainBall.characterId == 0) {
        if (IsKeyDown(KEY_UP))    mainBall.acelerate_y(-0.1f);
        if (IsKeyDown(KEY_DOWN))  mainBall.acelerate_y(0.1f);
        if (IsKeyDown(KEY_LEFT))  mainBall.acelerate_x(-0.1f);
        if (IsKeyDown(KEY_RIGHT)) mainBall.acelerate_x(0.1f);
        if (IsKeyDown(KEY_SPACE)) {
            float breakForce = 0.05f;
            mainBall.vx -= mainBall.vx * breakForce;
            mainBall.vy -= mainBall.vy * breakForce;
        }
    }
    
    // Duet Ball apenas ativado na tecla D para testes
    if (mainBall.characterId == 5 && IsKeyPressed(KEY_D)) {
        if (balls.size() < 4) {
            player newBall = mainBall; // Copia a bola principal
            newBall.x += GetRandomValue(-30, 30);
            newBall.y += GetRandomValue(-30, 30);
            newBall.vx = GetRandomValue(-3, 3);
            newBall.vy = GetRandomValue(-3, 3);
            balls.push_back(newBall);
        }
    }
   

    // Desenha obstáculos
    // TODO: fazer com que as paredes sejam desenhadas de acordo com a fase
    for (auto &seg : p_walls) {
        DrawLineV(seg.first, seg.second, RED);
    }

    // Atualiza posição e verifica colisao com paredes
    for (auto& b : balls) {
    Vector2 pos = { b.x, b.y };
    Vector2 vel = { b.vx, b.vy };
    float r = b.radius;

    // Colisão com paredes
    for (auto &seg : walls) {
        Vector2 cp, normal;
        if (CheckCollisionCircleLine(pos, r, seg.first, seg.second, cp, normal)) {
            PlaySound(ball_collision); // Som
            float dot = Dot(vel, normal);
            vel = Sub(vel, Scale(normal, 2 * dot));
            pos = Add(cp, Scale(normal, r));
            break;
        }
    }

    // Colar o bumper

    // Verifica bordas da tela para evitar sair da tela mesmo com colisão
    if (pos.x - r < 0) {
        pos.x = r;
        vel.x *= -1;
    }
    if (pos.x + r > screenWidth) {
        pos.x = screenWidth - r;
        vel.x *= -1;
    }
    if (pos.y - r < 0) {
        pos.y = r;
        vel.y *= -1;
    }
    if (pos.y + r > screenHeight) {
        pos.y = screenHeight - r;
        vel.y *= -1;
    }

    // Adiciona gravidade
    vel.y += 0.1f; // Simula gravidade

    // Aplica nova posição e velocidade ao player
    b.x = pos.x;
    b.y = pos.y;
    // Limita a velocidade
    vel.x = Clamp(vel.x, -5.0f, 5.0f);
    vel.y = Clamp(vel.y, -5.0f, 5.0f);
    b.vx = vel.x;
    b.vy = vel.y;

    for (auto& b : balls) {
        b.move();
        b.draw();
    }

    EndDrawing();
    }
}