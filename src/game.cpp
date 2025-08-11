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
	select_fundo = LoadTexture("assets/images/select_fundo1.png");
    bumperSound = LoadSound("assets/sounds/bumper.wav");
    ball_collision = LoadSound("assets/sounds/collision.wav");

    // Carrega a música do jogo apenas uma vez (com verificação robusta)
    gameMusic = LoadMusicStream("assets/sounds/spacejam.mp3");
    musicLoaded = false; // Flag para controlar quando iniciar a música

	frame = 0;
	timer = 0.0f;
	frameDuration = 5.0f;

    //cinematicMusic = LoadMusicStream("assets/sounds/cinematic_music.mp3");
    //SetMusicVolume(cinematicMusic, 0.5f);

    //Inicializa o LeBall
    leBallActive = false;
    leBallTimer = 0.0f;
    leBallCooldown = 0.0f; 

    // Paredes externas
    walls = {
        {{0, 0}, {screenWidth, 0}},                    // Topo
        {{screenWidth, 0}, {screenWidth, screenHeight}},  // Direita
        {{0, screenHeight}, {800.0f - HOLE_WIDTH, screenHeight}},  // Fundo esquerdo
        {{800.0f + HOLE_WIDTH, screenHeight}, {screenWidth, screenHeight}},  // Fundo direito
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

    // Inicializa variáveis do lançador (plunger)
    launcherAreaWidth = 80.0f;
    launcherAreaPos = {1125.0f, 350.0f};  // Movido mais para a esquerda
    plungerWidth = 70.0f;  // Aumentado o tamanho
    plungerHeight = 20.0f;  // Aumentado o tamanho
    plungerPos = {1140.0f, screenHeight - plungerHeight};  // Movido mais para a esquerda e mais para baixo
    plungerMaxPower = 100.0f;  // Força máxima do lançador
    plungerCurrentPower = 0.0f;
    plungerCharging = false;
    ballInLauncher = false;

    // Inicializa variáveis de controle de tempo após lançamento
    timeSinceLaunch = 0.0f;
    ballWasLaunched = false;

    // Inicializa variáveis de tempo e habilidades especiais
    playTimer = 0.0f;
    buttonPressTime = -1.0f; // -1 indica que não há habilidade ativa

}

void Game::loadPhase(const GamePhase& phase, player& p) {
    this->p_walls = phase.walls;
    this->bumpers = phase.bumpers;
    p.setPosition(phase.initialBallPosition.x, phase.initialBallPosition.y);
    
    // Reinicia a música quando carrega uma nova fase
    restartMusic();
}

void Game::restartMusic() {
    // Para a música atual
    StopMusicStream(gameMusic);
    
    // Reinicia a música do início
    PlayMusicStream(gameMusic);
    SetMusicVolume(gameMusic, 0.5f);
    
    // Marca como carregada para evitar conflitos
    musicLoaded = true;
}

//descarrega texturas e musica
Game::~Game() {
	UnloadTexture(alienship);
	UnloadTexture(alienPinball);
	UnloadTexture(pinballBall);
    UnloadTexture(select_fundo);
    UnloadSound(bumperSound);
    UnloadSound(ball_collision);
    
    // Descarrega a música sem parar explicitamente (o Raylib cuida disso)
    UnloadMusicStream(gameMusic);
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
        "JPBall",
        "Jessball",
        "LeBall",
        "E-Ball",
        "SamiBall",
        "Iv-Ball"
    };

    const char* characterPowers[] = {
        "- Cntrl Ball: controla bola levemente",
        "- Score Ball: pontuação 2x",
        "- Stop Ball: nao deixa bola cair",
        "- Grav Ball: reduz a gravidade",
        "- Tera Ball: bola aumentada",
        "- Duet Ball: invoca ate 4 bolas"

    };

    BeginDrawing();
    ClearBackground(BLACK);

    float scaleX = (float)screenWidth * 0.8f / select_fundo.width;
    float scaleY = (float)screenHeight * 0.8f / select_fundo.height;
    float scale = fmaxf(scaleX, scaleY); 
    Vector2 pos = { 
        (screenWidth - select_fundo.width * scale) / 2.0f,
        (screenHeight - select_fundo.height * scale) / 2.0f
    };
    DrawTextureEx(select_fundo, pos, 0.0f, scale, WHITE);

    Vector2 mousePos = GetMousePosition();

    for (int i = 0; i < numCharacters; i++) {
        Rectangle btn = { screenWidth / 2 - 200, 250.0f + i * 70.0f, 400, 50 };
        bool hovered = CheckCollisionPointRec(mousePos, btn);


        Color verdeagua = {43, 253, 175, 255};
        Color vermelhobbd = {252, 16, 87, 255};
        Color roxolegal = {171, 25, 111, 255};
        DrawRectangleRounded(btn, 0.3, 0, hovered ? RAYWHITE : verdeagua);
        DrawText(characterNames[i], btn.x + 10, btn.y + 15, 20, vermelhobbd);
        DrawText(characterPowers[i], btn.x + 80, btn.y + 33, 16, roxolegal);


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
        "O Monitor"
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
               return Game::YOU_WIN;
           } 
       }else {
            return Game::GAME_OVER; // Fase desconhecida
        }
   }
    EndDrawing();
    
    return game_state; // Retorna o estado do jogo
}

Game::GameState Game::win_screen(GameState game_state, char fase[CODE_SIZE], player &p) {

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Você venceu!", screenWidth / 2 - MeasureText("Você venceu!", 40) / 2, screenHeight / 2 - 20, 40, GREEN);
    DrawText("Pressione ENTER para continuar", screenWidth / 2 - MeasureText("Pressione ENTER para continuar", 20) / 2, screenHeight / 2 + 30, 20, WHITE);
    EndDrawing();

    if (IsKeyPressed(KEY_ENTER)) {
        return Game::MENU;
    }

    return game_state;
}

Game::GameState Game::game_over_screen(GameState game_state, char fase[CODE_SIZE], player &p) {

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Game Over", screenWidth / 2 - MeasureText("Game Over", 40) / 2, screenHeight / 2 - 20, 40, RED);
    DrawText("Pressione ENTER para continuar", screenWidth / 2 - MeasureText("Pressione ENTER para continuar", 20) / 2, screenHeight / 2 + 30, 20, WHITE);
    EndDrawing();

    if (IsKeyPressed(KEY_ENTER)) {
        return Game::MENU;
    }

    return game_state;
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

    // Inicializa a música apenas uma vez quando entra no jogo
    if (!musicLoaded) {
        PlayMusicStream(gameMusic);
        SetMusicVolume(gameMusic, 0.5f);
        musicLoaded = true;
    }

    // Atualiza a música apenas uma vez por frame
    UpdateMusicStream(gameMusic);

    // Bloco contagem de tempo
    playTimer += GetFrameTime();
    int totalSeconds = (int)playTimer;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    DrawText(TextFormat("Tempo: %02d:%02d", minutes, seconds), 10, screenHeight-30, 20, WHITE);

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

    //verifica LeBall
    float timeleBall = GetFrameTime();
    if (leBallActive) {
        leBallTimer -= timeleBall;
        if (leBallTimer <= 0.0f) 
        {
            leBallActive = false; // Desativa LeBall após o tempo acabar
        }         
    }
    if(leBallCooldown > 0.0f) {
        leBallCooldown -= timeleBall; 
    }

    if (leBallActive)
    {
        Vector2 leBallWallStart = {800.0f - HOLE_WIDTH, screenHeight};
        Vector2 leBallWallEnd = {800.0f + HOLE_WIDTH, screenHeight};
        DrawLineV(leBallWallStart, leBallWallEnd, PURPLE);
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
                PlaySound(bumperSound); // Toca o som do bumper

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

    // --- Lógica do Lançador (Plunger) ---
    // Verifica se a bola está na área do lançador (usando as variáveis do construtor)
    ballInLauncher = false;
    for (auto& ball : balls) {
        if (ball.x >= (launcherAreaPos.x - 20.0f) && ball.x <= (launcherAreaPos.x + launcherAreaWidth + 20.0f) && 
            ball.y >= launcherAreaPos.y && ball.y <= (plungerPos.y + 30.0f)) {
            ballInLauncher = true;
            break;
        }
    }

    // Input do lançador (tecla SPACE)
    if (ballInLauncher && IsKeyDown(KEY_SPACE)) {
        plungerCharging = true;
        plungerCurrentPower += GetFrameTime() * 500.0f; // Carrega a força
        if (plungerCurrentPower > plungerMaxPower) {
            plungerCurrentPower = plungerMaxPower;
        }
    } else if (plungerCharging && IsKeyReleased(KEY_SPACE)) {
        // Lança a bola quando solta o SPACE
        if (ballInLauncher) {
            for (auto& ball : balls) {
                if (ball.x >= (launcherAreaPos.x - 20.0f) && ball.x <= (launcherAreaPos.x + launcherAreaWidth + 20.0f) && 
                    ball.y >= launcherAreaPos.y && ball.y <= (plungerPos.y + 30.0f)) {
                    // Aplica força para cima baseada na força carregada
                    float forceMultiplier = plungerCurrentPower / plungerMaxPower;
                    ball.vy = -forceMultiplier * 25.0f; // Força aumentada para o lançador (negativo = para cima)
                    ball.vx += (rand() % 3 - 1) * 0.5f; // Pequena variação horizontal aleatória
                    PlaySound(ball_collision); // Som do lançamento
                    
                    // Inicia contagem de tempo após lançamento
                    ballWasLaunched = true;
                    timeSinceLaunch = 0.0f;
                    break;
                }
            }
        }
        plungerCharging = false;
        plungerCurrentPower = 0.0f;
    }
    
    // Desenha o lançador (plunger) - usando as variáveis do construtor
    Color plungerColor = plungerCharging ? RED : GRAY;
    float plungerOffset = plungerCharging ? (plungerCurrentPower / plungerMaxPower) * 25.0f : 0.0f;
    DrawRectangle(plungerPos.x, plungerPos.y + plungerOffset, plungerWidth, plungerHeight, plungerColor);
    
    // Desenha barra de força do lançador (usando as variáveis do construtor)
    if (ballInLauncher) {
        DrawText("SPACE para lançar", launcherAreaPos.x - 150, launcherAreaPos.y - 30, 14, WHITE);
        if (plungerCharging) {
            float barWidth = 100.0f;
            float barHeight = 10.0f;
            float powerPercent = plungerCurrentPower / plungerMaxPower;
            DrawRectangle(launcherAreaPos.x - 20, launcherAreaPos.y - 15, barWidth, barHeight, DARKGRAY);
            DrawRectangle(launcherAreaPos.x - 20, launcherAreaPos.y - 15, barWidth * powerPercent, barHeight, 
                         powerPercent < 0.7f ? GREEN : (powerPercent < 0.9f ? YELLOW : RED));
        }
    }
    
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

    if (balls[0].characterId == 2)  // LeBall
    {
        if (IsKeyPressed(KEY_L) && !leBallActive && leBallCooldown <= 0.0f) 
        {
            leBallActive = true;
            leBallTimer = 10.0f; // Tempo que LeBall fica ativo
            leBallCooldown = 30.0f; // Tempo de recarga do LeBall
        }
        
        if (leBallActive){
            DrawText(TextFormat("LeBall!: %.1fs", leBallTimer), 20, 40, 16, YELLOW);            
        }
        else if (leBallCooldown > 0.0f) {
            DrawText(TextFormat("LeBall disponivel em: %.1fs", leBallCooldown), 20, 40, 16, PURPLE);
        }
        else {
            DrawText("Pressione L para ativar LeBall!", 20, 40, 16, YELLOW);
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

    
    // Poder de redução da gravidade
    if (balls[0].characterId == 3) {
        if (IsKeyPressed(KEY_D) && buttonPressTime < 0.0f){
            buttonPressTime = playTimer;
        }
        if (buttonPressTime >= 0.0f){
            float elapsed = playTimer - buttonPressTime;
            if (elapsed <= 30.0f){
                balls[0].acelerate_y(-0.05f);
                DrawText(TextFormat("BOOST ATIVO: %.1f segs restantes", 30.0f - elapsed), 10, 70, 20, GREEN);
            }
            else{
                buttonPressTime = -1.0f;
            }
        }
    }

    //Poder de aumentar a bola
    if (balls[0].characterId == 4) {
        if (IsKeyPressed(KEY_D) && buttonPressTime < 0.0f){
            buttonPressTime = playTimer;
        }
        if (buttonPressTime >= 0.0f){
            float elapsed = playTimer - buttonPressTime;
            if (elapsed <= 30.0f){
                balls[0].radius = 25;
                DrawText(TextFormat("BOOST ATIVO: %.1f segs restantes", 30.0f - elapsed), 10, 70, 20, GREEN);
            }
            else{
                buttonPressTime = -1.0f;
                balls[0].radius = 10;
            }
        }
    }



    // Atualiza posição e verifica colisao com paredes
    for (auto& b : balls) {
        Vector2 pos = { b.x, b.y };
        Vector2 vel = { b.vx, b.vy };
        float r = b.radius;

        // Adiciona gravidade primeiro
        if (!ballInLauncher) vel.y += 0.1f; 
        // Aplica movimento
        pos.x += vel.x;
        pos.y += vel.y;

        if(!leBallActive && pos.y - r > screenHeight) {
            game_state = SCOREBOARD; 
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

        // Colisão com a parede temporária do LeBall (se ativa)
        if (leBallActive) {
            Vector2 leBallWallStart = {800.0f - HOLE_WIDTH, screenHeight};
            Vector2 leBallWallEnd = {800.0f + HOLE_WIDTH, screenHeight};
            Vector2 cp, normal;
            if (CheckCollisionCircleLine(pos, r, leBallWallStart, leBallWallEnd, cp, normal)) {
                PlaySound(ball_collision);
                float dot = Dot(vel, normal);
                vel = Sub(vel, Scale(normal, 2 * dot));
                pos = Add(cp, Scale(normal, r));
                // Impulso extra para cima quando bate na parede LeBall
                vel.y -= 2.0f;
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

        // Atualiza o tempo desde o lançamento
        if (ballWasLaunched) {
            timeSinceLaunch += GetFrameTime();
            if (timeSinceLaunch >= 1.0f) {  // 1 segundo depois do lançamento
                ballWasLaunched = false;  // Desativa o modo de velocidade alta
            }
        }

        // Limita a velocidade baseado no tempo desde o lançamento
        if (ballWasLaunched && timeSinceLaunch < 1.0f) {
            // Primeiro segundo após lançamento: permite velocidade maior
            vel.x = Clamp(vel.x, -12.0f, 12.0f);
            vel.y = Clamp(vel.y, -30.0f, 12.0f);
        } else {
            // Velocidade normal após 1 segundo
            vel.x = Clamp(vel.x, -6.0f, 6.0f);
            vel.y = Clamp(vel.y, -6.0f, 6.0f);
        }

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
