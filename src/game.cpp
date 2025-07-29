#include "game.h"
#include "bumper.h"
#include "utility.h"

int HOLE_WIDTH = 100; // Largura do buraco na parede direita

// Inicializa o jogo com paredes de borda e paredes internas
Game::Game(float width, float height) {
    screenWidth = width;
    screenHeight = height;

    
    // Paredes externas
    walls = {
        {{0, 0}, {screenWidth, 0}},                    // Topo
        {{screenWidth, 0}, {screenWidth, screenHeight}},  // Direita
        {{screenWidth/2 - HOLE_WIDTH, screenHeight}, {screenWidth/2 + HOLE_WIDTH, screenHeight}},  // Fundo
        {{0, screenHeight}, {0, 0}}                    // Esquerda
    };

    // Inicializa variáveis dos flipers
    flipperLength = 80.0f;
    leftFlipperPos = {screenWidth * 0.35f, screenHeight - 100.0f};
    rightFlipperPos = {screenWidth * 0.65f, screenHeight - 100.0f};
    leftFlipperAngle = 30.0f;  // Ângulo inicial do fliper esquerdo (apontando para baixo-direita)
    rightFlipperAngle = 180.0f-30.0f;  // Ângulo inicial do fliper direito (apontando para baixo-esquerda)
    leftFlipperPressed = false;
    rightFlipperPressed = false;

}

void Game::loadPhase(const GamePhase& phase, player& p) {
    this->p_walls = phase.walls;
    this->bumpers = phase.bumpers;
    p.setPosition(phase.initialBallPosition.x, phase.initialBallPosition.y);
}

// Função de menu (placeholder)
Game::GameState Game::menu(GameState game_state, char fase[CODE_SIZE], player &p) {

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
                loadPhase(p1_phase_data, p); // Carrega a fase 1 usando a nova estrutura
                return PLAYING; // Muda para o estado de jogo
            }
        
    }else if(mousePos.x >= screenWidth / 2 - 150 && mousePos.x <= screenWidth / 2 + 150 &&
        mousePos.y >= screenHeight / 2 - 50 && mousePos.y <= screenHeight / 2) {
        
        DrawRectangleRounded({screenWidth / 2 - 150, screenHeight / 2 - 50, 300, 50}, 0.5,0, RAYWHITE);
        DrawText("Continue", screenWidth / 2 - 50 , screenHeight / 2 - 35, 20, RED);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {    
            EndDrawing();  
            return CONTINUE_MENU; 
        }
        

    }else if (IsKeyPressed(KEY_ESCAPE)) {
        return GAME_OVER; // Sai do menu
    }
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo

}

Game::GameState Game::continue_menu(GameState game_state, char fase[CODE_SIZE], player &p) {
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
            letterCount++;
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
                if(strcmp(fase, "") == 0 || strcmp(fase, "fase1") == 0) {
                    strcpy(fase, "fase1");
                    loadPhase(p1_phase_data, p); // Carrega a fase 1
                } else if (strcmp(fase, "fase2") == 0) {
                    loadPhase(p2_phase_data, p); // Carrega a fase 2
                } else {
                    std::cout << "Fase desconhecida: " << fase << std::endl;
                    strcpy(fase, "fase1");
                    loadPhase(p1_phase_data, p);
                }
                return PLAYING;
            }
        
    }
    
    
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
        return MENU; // Sai do menu
    }
    
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo
}

Game::GameState Game::Scoreboard(GameState game_state, char fase[CODE_SIZE], player &p) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Scoreboard Placeholder", screenWidth / 2 - 100, screenHeight / 2 - 20, 20, WHITE);
    
    if (IsKeyPressed(KEY_ESCAPE)) {
        return MENU; // Retorna ao menu
    }
    
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo
}


// Função principal de jogo
Game::GameState Game::play_step(GameState game_state, char fase[CODE_SIZE], player &p) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    // Input
    if (IsKeyDown(KEY_UP))    p.acelerate_y(-0.1f);
    if (IsKeyDown(KEY_DOWN))  p.acelerate_y(0.1f);
    if (IsKeyDown(KEY_LEFT))  p.acelerate_x(-0.1f);
    if (IsKeyDown(KEY_RIGHT)) p.acelerate_x(0.1f);
    if (IsKeyDown(KEY_SPACE)) {
        float breakForce = 0.05;
        p.vx -= p.vx * breakForce;
        p.vy -= p.vy * breakForce;
    }
    // Desenha obstáculos
    // TODO: fazer com que as paredes sejam desenhadas de acordo com a fase
    // Desenha as paredes FIXAS (bordas da tela)
    for (auto &seg : walls) {
        DrawLineV(seg.first, seg.second, RED);
    }
    
    // Desenha as paredes ESPECÍFICAS DA FASE
    for (auto &seg : p_walls) { 
        DrawLineV(seg.first, seg.second, RED);
    }

    // Atualiza posição
    Vector2 pos = {p.x, p.y};
    Vector2 vel = {p.vx, p.vy};
    float r = p.radius;

    if (pos.y - 2 * r > screenHeight) {
        game_state = SCOREBOARD; // Se cair no buraco, game over
    }
    // Verifica colisão com paredes
    for (auto &seg : walls) {
        Vector2 cp, normal;
        if (CheckCollisionCircleLine(pos, r, seg.first, seg.second, cp, normal)) {
            PlaySound(Game::ball_collision); // Toca som de colisão
            float dot = Dot(vel, normal);
            vel = Sub(vel, Scale(normal, 2 * dot));
            pos = Add(cp, Scale(normal, r));
            //vel = Scale(vel, 0.8f); // Aplica um fator de atrito
            break;
        }
    }

    //colisao c paredes da fase
    for (auto &seg : p_walls) { 
        Vector2 cp, normal;
        if (CheckCollisionCircleLine(pos, r, seg.first, seg.second, cp, normal)) {
            PlaySound(Game::ball_collision);
            float dot = Dot(vel, normal);
            vel = Sub(vel, Scale(normal, 2 * dot));
            pos = Add(cp, Scale(normal, r));
            break; // importante p parar apos primeira colisao
        }
    }

    // --- Colisão com Bumpers ---
    float deltaTime = GetFrameTime(); // Tempo entre frames para animação
    for (Bumper& bumper : bumpers) {
        Vector2 normal;
        Vector2 diff = Sub(pos, bumper.position); 
        float distance = Length(diff); 
        float minDistance = bumper.radius + r;
        float penetration = 0.0f;

        if (distance <= minDistance) {
            normal = Normalize(diff); 
            penetration = minDistance - distance;

            bumper.onHit(); // Ativa o efeito visual do bumper
            PlaySound(bumpsound); 

            // Separação para evitar que a bola fique presa
            pos = Add(pos, Scale(normal, penetration)); 

            // Cálculo da reflexão (similar à parede, mas com um "impulso" extra)
            float dot = Dot(vel, normal); 
            vel = Sub(vel, Scale(normal, 2 * dot)); 

            // Adiciona uma força extra ao refletir do bumper
            float bumperForce = 3.0f; 
            vel = Add(vel, Scale(normal, bumperForce)); 
        }
        bumper.update(deltaTime); // Atualiza a animação do bumper
        bumper.draw(); // Desenha o bumper
    }


    // Colar o fliper de pinball
    
    // Input dos flipers
    leftFlipperPressed = IsKeyDown(KEY_Q);
    rightFlipperPressed = IsKeyDown(KEY_E);
    
    // Atualiza ângulos dos flipers baseado no input
    float flipperSpeed = 5.0f;
    
    // Fliper esquerdo: rotaciona de 30° para -30° quando acionado
    if (leftFlipperPressed) {
        leftFlipperAngle = Clamp(leftFlipperAngle - flipperSpeed, -30.0f, 30.0f);
    } else {
        leftFlipperAngle = Clamp(leftFlipperAngle + flipperSpeed, -30.0f, 30.0f);
    }
    
    // Fliper direito: rotaciona de -30° para 30° quando acionado  
    if (rightFlipperPressed) {
        rightFlipperAngle = Clamp(rightFlipperAngle + flipperSpeed, 180.0f-30.0f, 180.0f + 30.0f);
    } else {
        rightFlipperAngle = Clamp(rightFlipperAngle - flipperSpeed, 180.0f-30.0f, 180.0f +30.0f);
    }
    
    // Calcula as posições finais dos flipers
    float leftAngleRad = leftFlipperAngle * PI / 180.0f;
    float rightAngleRad = rightFlipperAngle * PI / 180.0f;
    
    Vector2 leftFlipperEnd = {
        leftFlipperPos.x + (float)cos(leftAngleRad) * flipperLength,
        leftFlipperPos.y + (float)sin(leftAngleRad) * flipperLength
    };
    
    Vector2 rightFlipperEnd = {
        rightFlipperPos.x + (float)cos(rightAngleRad) * flipperLength,
        rightFlipperPos.y + (float)sin(rightAngleRad) * flipperLength
    };
    
    // Verifica colisão com flipers
    Vector2 cp, normal;
    
    // Colisão com fliper esquerdo
    if (CheckCollisionCircleLine(pos, r, leftFlipperPos, leftFlipperEnd, cp, normal)) {
        PlaySound(Game::ball_collision);
        float dot = Dot(vel, normal);
        vel = Sub(vel, Scale(normal, 2 * dot));
        pos = Add(cp, Scale(normal, r));
        
        // Adiciona força extra se o fliper estiver sendo acionado
        if (leftFlipperPressed) {
            Vector2 flipperForce = {(float)cos(leftAngleRad) * 3.0f, (float)sin(leftAngleRad) * 3.0f};
            vel = Add(vel, flipperForce);
        }
    }
    
    // Colisão com fliper direito
    if (CheckCollisionCircleLine(pos, r, rightFlipperPos, rightFlipperEnd, cp, normal)) {
        PlaySound(Game::ball_collision);
        float dot = Dot(vel, normal);
        vel = Sub(vel, Scale(normal, 2 * dot));
        pos = Add(cp, Scale(normal, r));
        
        // Adiciona força extra se o fliper estiver sendo acionado
        if (rightFlipperPressed) {
            Vector2 flipperForce = {(float)cos(rightAngleRad) * 3.0f, (float)sin(rightAngleRad) * 3.0f};
            vel = Add(vel, flipperForce);
        }
    }
    
    // Desenha os flipers
    DrawLineEx(leftFlipperPos, leftFlipperEnd, 8.0f, leftFlipperPressed ? YELLOW : WHITE);
    DrawLineEx(rightFlipperPos, rightFlipperEnd, 8.0f, rightFlipperPressed ? YELLOW : WHITE);
    DrawCircleV(leftFlipperPos, 6.0f, GRAY);   // Ponto de rotação
    DrawCircleV(rightFlipperPos, 6.0f, GRAY);  // Ponto de rotação


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
    if (pos.y + r > screenHeight && pos.x < screenWidth/2 - HOLE_WIDTH && pos.x > screenWidth/2 + HOLE_WIDTH) {
        pos.y = screenHeight - r;
        vel.y *= -1;
    }

    // Adiciona gravidade
    //vel.y += 0.1f; // Simula gravidade

    // Aplica nova posição e velocidade ao player
    p.x = pos.x;
    p.y = pos.y;
    // Limita a velocidade
    vel.x = Clamp(vel.x, -5.0f, 5.0f);
    vel.y = Clamp(vel.y, -5.0f, 5.0f);
    p.vx = vel.x;
    p.vy = vel.y;

    p.move();   // atualiza a posição com a velocidade
    p.draw();   // desenha o jogador

    EndDrawing();
    return game_state; // Retorna o estado do jogo
}