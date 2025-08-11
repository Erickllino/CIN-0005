#include "raylib.h"
#include <vector>
#include <iostream>

struct Linha {
    Vector2 inicio;
    Vector2 fim;
};

int main() {
    int larguraTela = 1280;
    int alturaTela = 800;

    InitWindow(larguraTela, alturaTela, "editor de Mapa");

    Texture2D desenho_fase = LoadTexture("imageFases/fase2.png");

    SetTargetFPS(60);

    std::vector<Linha> linhas;

    bool desenhando = false;
    
    Vector2 pontoInicial;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_C)) {
            linhas.clear(); 
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            
            if (desenhando == false) { // é o primeiro ponto
                desenhando = true;
                pontoInicial = GetMousePosition();
            } 
            else {
                desenhando = false; // é o ponto final
                
                Vector2 pontoFinal = GetMousePosition();

                //nova linha com o ponto inicial e final
                Linha novaLinha;
                novaLinha.inicio = pontoInicial;
                novaLinha.fim = pontoFinal;

                linhas.push_back(novaLinha);

                //imprime as coordenadas dos pontos
                std::cout <<"{{"<< pontoInicial.x<<","<< pontoInicial.y <<"}"<<","<<"{"<<pontoFinal.x<<","<<pontoFinal.y<<"}}"<< std::endl;
            }

        }
        BeginDrawing();
        ClearBackground(BLACK); 

        if (desenho_fase.id > 0) {
            DrawTexture(desenho_fase, 0, 0, WHITE);
        }
        // e se nao tiver imagem fica tela preta

        for (int i = 0; i < linhas.size(); i++) {
            Linha linhaAtual = linhas[i];
            DrawLineV(linhaAtual.inicio, linhaAtual.fim, RED);
        }
        
        if (desenhando == true) {
            DrawLineV(pontoInicial, GetMousePosition(), RED); //desenha do primeiro ponto ate o ponto atual
        }

        EndDrawing();
    }
    UnloadTexture(desenho_fase);
    CloseWindow();

    return 0;
}