#include "game.h"
#include "bumper.h"
#include "utility.h"
#include <string>
#include <algorithm>

float HOLE_WIDTH = 100.0f; // Largura do buraco na parede direita

// Inicializa o jogo com paredes de borda e paredes internas
Game::Game(float width, float height) {
    screenWidth = width;
    screenHeight = height;

	//carrega textura
	alienship = LoadTexture("assets/images/alienship.png");
	alienPinball = LoadTexture("assets/images/alienpinball.png");
	pinballBall = LoadTexture("assets/images/pinballBall.png");

	frame = 0;
	timer = 0.0f;
	frameDuration = 5.0f;

    //cinematicMusic = LoadMusicStream("assets/sounds/cinematic_music.mp3");
    //SetMusicVolume(cinematicMusic, 0.5f);

    // Paredes externas
    walls = {
        {{0, 0}, {screenWidth, 0}},                    // Topo
        {{screenWidth, 0}, {screenWidth, screenHeight}},  // Direita
        {{0, screenHeight}, {800.0f - HOLE_WIDTH, screenHeight}},  // Fundo
        {{800.0f + HOLE_WIDTH, screenHeight}, {screenWidth, screenHeight}},  // Fundo
        {{0, screenHeight}, {0, 0}}                    // Esquerda
    };

    // Inicializa variáveis dos flipers
    flipperLength = 90.0f;
    leftFlipperPos = {700, screenHeight - 60.0f};
    rightFlipperPos = {900, screenHeight - 60.0f};
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

//descarrega texturas e musica
Game::~Game() {
	UnloadTexture(alienship);
	UnloadTexture(alienPinball);
	UnloadTexture(pinballBall);
    //UnloadMusicStream(cinematicMusic);
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
                p.score = 0; // reseta a pontuacao
                strcpy(fase, "fase1");
                balls.clear();
                loadPhase(p1_phase_data, p); // Carrega a fase 1
                balls.push_back(p);
                return CINEMATIC; // Muda para o estado cinematográfico
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

Game::GameState Game::selectCharacter(GameState game_state, char fase[CODE_SIZE], player &p) {
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
        Rectangle btn = { screenWidth / 2 - 200, 100.0f + i * 70.0f, 400, 50 };
        bool hovered = CheckCollisionPointRec(mousePos, btn);

        DrawRectangleRounded(btn, 0.3, 0, hovered ? RAYWHITE : DARKGRAY);
        DrawText(characterNames[i], btn.x + 10, btn.y + 10, 20, RED);
        DrawText(characterPowers[i], btn.x + 220, btn.y + 10, 16, WHITE);

        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedCharacter = i;

            // Aqui você pode usar selectedCharacter para definir o personagem no player p
            p.characterId = selectedCharacter;
            
            // Atualiza também o characterId na bola que está no vetor balls
            if (!balls.empty()) {
                balls[0].characterId = selectedCharacter;
            }

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

Game::GameState Game::continue_menu(GameState game_state, char fase[CODE_SIZE], player &p) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Digite o codigo da fase", screenWidth / 2 - 125, screenHeight / 2 - 200, 20, WHITE);
    
    int key = GetCharPressed();
    
    int letterCount = strlen(fase); // Tamanho máximo do código

    while (key > 0){
        // NOTE: Only allow keys in range [32..125]
        if ((key >= 32) && (key <= 125) && (letterCount < CODE_SIZE - 1))
        {
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
                    p.score = 0;
                    strcpy(fase, "fase1");
                    balls.clear();
                    loadPhase(p1_phase_data, p); // Carrega a fase 1
                    balls.push_back(p);
                } else if (strcmp(fase, "fase2") == 0) {
                    p.score = 0;
                    balls.clear();
                    loadPhase(p2_phase_data, p); // Carrega a fase 2
                    balls.push_back(p);
                } else {
                    std::cout << "Fase desconhecida: " << fase << std::endl;
                    strcpy(fase, "fase1");
                    p.score = 0;
                    balls.clear();
                    loadPhase(p1_phase_data, p);
                    balls.push_back(p);
                }
                return CHARACTER_SELECTION; 
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
    
    DrawText("Scoreboard", screenWidth / 2 - 220, 220, 65, WHITE);

    // Aliens:
    // - Ivison Rafael
    // - O real Joao Pinto bola
    // - Egito T.
    // - GC
    // - TT
    // - Zé Ninguém
    const char* Alien_names[] = {
        "Ivison Rafael ",
        "O real Joao Pinto bola ",
        "Egito T. ",
        "GC ",
        "TT ",
        "Zé Ninguém ",
        "Lebron James ",    
        "Neymar ",
        "Vasco da Gama",
        ""
    };


    // Os aliens só são sorteados ao mudar de fase
    static std::vector<std::pair<const char*, int>> aliens;      // (nome, score)
    static std::string last_fase = "";                          // Para regenerar ao trocar de fase

    // Trata fase vazia como "fase1" para consistência (evita scoreboard vazio / acesso inválido)
    if (fase[0] == '\0') {
        strcpy(fase, "fase1");
    }

    // (Re)gera a lista quando muda a fase ou se por algum motivo ficou vazia
    if (last_fase != std::string(fase) || aliens.empty()) {
        aliens.clear();
        std::vector<const char*> names(Alien_names, Alien_names + sizeof(Alien_names)/sizeof(Alien_names[0]));
        std::random_shuffle(names.begin(), names.end()); // (Manter por compatibilidade – escopo não inclui refator #8)
        for (int i = 0; i < 4 && i < (int)names.size(); i++) {
            int score = GetRandomValue(900, 1100);
            aliens.push_back({names[i], score});
        }
        last_fase = std::string(fase);
    }

    // Atualiza / insere jogador
    const char* jogador_nome = "Você";
    bool jogador_presente = false;
    for (auto &a : aliens) {
        if (strcmp(a.first, jogador_nome) == 0) {
            a.second = p.score; // sincroniza score atual
            jogador_presente = true;
            break;
        }
    }
    if (!jogador_presente) {
        aliens.push_back({jogador_nome, p.score});
    }

    // Limita para no máximo 5 (mantém o jogador, já garantido acima)
    while ((int)aliens.size() > 5) {
        // Se o último for o jogador, troca antes de remover
        if (strcmp(aliens.back().first, jogador_nome) == 0) {
            std::swap(aliens.back(), aliens.front()); // move jogador para frente antes de truncar
        }
        aliens.pop_back();
    }

    // Segurança adicional: se mesmo assim estiver vazio (não deve ocorrer), repõe jogador
    if (aliens.empty()) {
        aliens.push_back({jogador_nome, p.score});
    }

   // Mostra a pontuação de todos em ordem decrescente
   std::sort(aliens.begin(), aliens.end(), [](const auto& a, const auto& b) {
       return a.second > b.second;
   });
   
   for (size_t i = 0; i < aliens.size(); i++) {
       const char* name = aliens[i].first;
       int score = aliens[i].second;
       Color color;
       
       if (i == 0){
            // passa um tempo como branco depois troca para GOLD
            
            timer += GetFrameTime();
            
            if (timer >= 0.5f && timer < 1.0f) {
               color = GOLD;
           }else if (timer < 0.5f) {
               color = WHITE;
           }else if (timer >= 1.0f) {
               color = GOLD;
               timer = 0.0f;
           }
       } else {
           color = WHITE;
       }
        DrawText(TextFormat("%d. %s: %d", i + 1, name, score), screenWidth / 2 - 250, 300 + i * 30, 20, color);
   }

   // Aperte enter para continuar
   DrawText("Pressione ENTER para continuar", screenWidth / 2 - 150, screenHeight - 50, 20, WHITE);
   if (IsKeyPressed(KEY_ENTER)) {
       // Proteção contra acesso inválido
       if (!aliens.empty() && strcmp(aliens[0].first, "Você") == 0) {
           // Jogador é o primeiro: avança lógica de fase
           aliens[0].second = p.score; // sincroniza (já está, mas mantém intenção – problema 17)
           if (strcmp(fase, "fase1") == 0) {
               strcpy(fase, "fase2");
               p.score = 0;
               // Recarrega completamente a fase 2 (problema 4)
               balls.clear();
               loadPhase(p2_phase_data, p);
               balls.push_back(p);
               return Game::PLAYING;
           } else if (strcmp(fase, "fase2") == 0) {
               std::cout << "Ganhou" << std::endl;
               return Game::GAME_OVER;
           } else {
               return Game::GAME_OVER; // Fase desconhecida
           }
       }
   }
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo
}

Game::GameState Game::cinematic_step(GameState game_state, char fase[CODE_SIZE], player &p) {

    BeginDrawing();
    ClearBackground(BLACK);

    timer += GetFrameTime();

    switch (frame) {
        case 0:
            // Imagem da nave alienígena chegando (redimensionada para caber na tela)
            {
                float scaleX = screenWidth * 0.8f / alienship.width;
                float scaleY = screenHeight * 0.8f / alienship.height;
                float scale = fminf(scaleX, scaleY); // Mantém proporção
                Vector2 pos = {screenWidth / 2 - (alienship.width * scale) / 2, screenHeight / 2 - (alienship.height * scale) / 2};
                DrawTextureEx(alienship, pos, 0.0f, scale, WHITE);
            }
            DrawText("Aliens invadiram a Terra!", screenWidth / 2 - MeasureText("Aliens invadiram a Terra!", 20) / 2, screenHeight - 80, 20, WHITE);
            break;
        case 1:
            // Imagem dos aliens perto de um pinball (redimensionada para caber na tela)
            {
                float scaleX = screenWidth * 0.8f / alienPinball.width;
                float scaleY = screenHeight * 0.8f / alienPinball.height;
                float scale = fminf(scaleX, scaleY); // Mantém proporção
                Vector2 pos = {screenWidth / 2 - (alienPinball.width * scale) / 2, screenHeight / 2 - (alienPinball.height * scale) / 2};
                DrawTextureEx(alienPinball, pos, 0.0f, scale, WHITE);
            }
            DrawText("Para decidir o futuro do mundo, eles propuseram um torneio de Pinball!", screenWidth / 2 - MeasureText("Para decidir o futuro do mundo, eles propuseram um torneio de Pinball!", 20) / 2, screenHeight - 80, 20, WHITE);
            break;
        case 2:
            // Imagem de alguém virando uma bola de pinball (redimensionada para caber na tela)
            {
                float scaleX = screenWidth * 0.8f / pinballBall.width;
                float scaleY = screenHeight * 0.8f / pinballBall.height;
                float scale = fminf(scaleX, scaleY); // Mantém proporção
                Vector2 pos = {screenWidth / 2 - (pinballBall.width * scale) / 2, screenHeight / 2 - (pinballBall.height * scale) / 2};
                DrawTextureEx(pinballBall, pos, 0.0f, scale, WHITE);
            }
            DrawText("Você está competindo para ser o Presidente do Mundo!", screenWidth / 2 - MeasureText("Você está competindo para ser o Presidente do Mundo!", 20) / 2, screenHeight - 80, 20, WHITE);
            break;
        default:
            // Fim da cinemática, transita para o jogo
            timer = 0.0f;
            return CHARACTER_SELECTION;
    }

    if (timer >= frameDuration) {
        frame++;
        timer = 0.0f;
    }

    // Pular cinemática com ENTER
    if (IsKeyPressed(KEY_ENTER)) {
        timer = 0.0f;
        return CHARACTER_SELECTION;
    }
    DrawText("Pressione ENTER para pular", screenWidth - 200, screenHeight - 20, 10, WHITE);


    EndDrawing();
    return game_state;
}


// Função principal de jogo
Game::GameState Game::play_step(GameState game_state, char fase[CODE_SIZE], player &p) {
    BeginDrawing();
    ClearBackground(BLACK);

    // exibe a pontuacao na pontuao
    DrawText(TextFormat("Score: %d", p.score), 20, 10, 20, RED);
    
    if (balls.empty()) { // verifica se há bolas
        EndDrawing();
        return game_state;
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

    // --- Colisão com Bumpers ---
    float deltaTime = GetFrameTime(); // Tempo entre frames para animação
    for (Bumper& bumper : bumpers) {
        // Verifica colisão de todas as bolas com este bumper
        for (auto& ball : balls) {
            Vector2 ballPos = {ball.x, ball.y};
            Vector2 ballVel = {ball.vx, ball.vy};
            float ballRadius = ball.radius;
            
            Vector2 normal;
            Vector2 diff = Sub(ballPos, bumper.position); 
            float distance = Length(diff); 
            float minDistance = bumper.radius + ballRadius;
            float penetration = 0.0f;

            if (distance <= minDistance) {
                normal = Normalize(diff); 
                penetration = minDistance - distance;

                bumper.onHit(); // Ativa o efeito visual do bumper
                PlaySound(bumpsound); 

                //pontuacao para cada bumper
                if (ball.characterId == 1) {
                    p.score += bumper.scoreValue * 2;
                }
                else {
                    p.score += bumper.scoreValue;
                }

                // Separação para evitar que a bola fique presa
                ballPos = Add(ballPos, Scale(normal, penetration)); 
                ball.x = ballPos.x;
                ball.y = ballPos.y;

                // Cálculo da reflexão (similar à parede, mas com um "impulso" extra)
                float dot = Dot(ballVel, normal); 
                ballVel = Sub(ballVel, Scale(normal, 2 * dot)); 

                // Adiciona uma força extra ao refletir do bumper
                float bumperForce = 3.0f; 
                ballVel = Add(ballVel, Scale(normal, bumperForce)); 
                
                ball.vx = ballVel.x;
                ball.vy = ballVel.y;
            }
        }
        bumper.update(deltaTime); // Atualiza a animação do bumper
        bumper.draw(); // Desenha o bumper
    }


    // Colar o fliper de pinball
    // Input dos flipers
    leftFlipperPressed = IsKeyDown(KEY_Q);
    rightFlipperPressed = IsKeyDown(KEY_E);
    
    // Atualiza ângulos dos flipers baseado no input
    float flipperSpeed = 3.0f;
    
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

    // Desenha os flipers
    DrawLineEx(leftFlipperPos, leftFlipperEnd, 20.0f, leftFlipperPressed ? YELLOW : WHITE);
    DrawLineEx(rightFlipperPos, rightFlipperEnd, 20.0f, rightFlipperPressed ? YELLOW : WHITE);
    DrawCircleV(leftFlipperPos, 10.0f, GRAY);   // Ponto de rotação
    DrawCircleV(rightFlipperPos, 10.0f, GRAY);  // Ponto de rotação


    
    // Começando a colocar os poderes aqui, já que a bola era controlada aqui
    if (balls[0].characterId == 0) {
        if (IsKeyDown(KEY_UP))    balls[0].acelerate_y(-0.1f);
        if (IsKeyDown(KEY_DOWN))  balls[0].acelerate_y(0.1f);
        if (IsKeyDown(KEY_LEFT))  balls[0].acelerate_x(-0.1f);
        if (IsKeyDown(KEY_RIGHT)) balls[0].acelerate_x(0.1f);
        if (IsKeyDown(KEY_SPACE)) {
            float breakForce = 0.05f;
            balls[0].vx -= balls[0].vx * breakForce;
            balls[0].vy -= balls[0].vy * breakForce;
        }
    }
    
    // Duet Ball apenas ativado na tecla D para testes
    if (balls[0].characterId == 5 && IsKeyPressed(KEY_D)) {
        if (balls.size() < 4) {
            player newBall = balls[0]; // Copia a bola principal
            newBall.x += GetRandomValue(-30, 30);
            newBall.y += GetRandomValue(-30, 30);
            newBall.vx = GetRandomValue(-3, 3);
            newBall.vy = GetRandomValue(-3, 3);
            balls.push_back(newBall);
        }
    }
   

    // Atualiza posição e verifica colisao com paredes
    for (auto& b : balls) {
        Vector2 pos = { b.x, b.y };
        Vector2 vel = { b.vx, b.vy };
        float r = b.radius;

        // Adiciona gravidade primeiro
        //vel.y += 0.1f; // Simula gravidade

        // Aplica movimento
        pos.x += vel.x;
        pos.y += vel.y;

        if (pos.y - r > screenHeight) {
            game_state = SCOREBOARD; // Se cair no buraco, game over
        }
        
        // Verifica colisão com paredes fixas
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

        // Verifica colisão com paredes da fase
        for (auto &seg : p_walls) { 
            Vector2 cp, normal;
            if (CheckCollisionCircleLine(pos, r, seg.first, seg.second, cp, normal)) {
                PlaySound(ball_collision);
                float dot = Dot(vel, normal);
                vel = Sub(vel, Scale(normal, 2 * dot));
                pos = Add(cp, Scale(normal, r));
                break; // importante p parar apos primeira colisao
            }
        }

        // Verifica colisão com flipers
        Vector2 cp, normal;
    
        // Colisão com fliper esquerdo
        if (CheckCollisionCircleLine(pos, r, leftFlipperPos, leftFlipperEnd, cp, normal)) {
            PlaySound(ball_collision);
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
            PlaySound(ball_collision);
            float dot = Dot(vel, normal);
            vel = Sub(vel, Scale(normal, 2 * dot));
            pos = Add(cp, Scale(normal, r));
            
            // Adiciona força extra se o fliper estiver sendo acionado
            if (rightFlipperPressed) {
                Vector2 flipperForce = {(float)cos(rightAngleRad) * 3.0f, (float)sin(rightAngleRad) * 3.0f};
                vel = Add(vel, flipperForce);
            }
        }

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
        if (pos.y + r > screenHeight && (pos.x < 800.0f - HOLE_WIDTH || pos.x > 800.0f + HOLE_WIDTH)) {
            pos.y = screenHeight - r;
            vel.y *= -1;
        }

        // Limita a velocidade
        vel.x = Clamp(vel.x, -6.0f, 6.0f);
        vel.y = Clamp(vel.y, -6.0f, 6.0f);

        // Aplica a nova posição e velocidade ao objeto
        b.x = pos.x;
        b.y = pos.y;
        b.vx = vel.x;
        b.vy = vel.y;
        
        b.draw();
    }
    EndDrawing();
    return game_state; // Retorna o estado do jogo
}
