/* #ifndef C879098C_893D_4CA3_B58B_27EF3BCC2AF8
#define C879098C_893D_4CA3_B58B_27EF3BCC2AF8

#include "raylib.h"
#include <vector>

using std::vector;
using std::pair;

// Declarações externas das variáveis (serão definidas no fases.cpp)
extern vector<pair<Vector2, Vector2>> p1_walls;
extern vector<pair<Vector2, Vector2>> p2_walls;

#endif */

#ifndef C879098C_893D_4CA3_B58B_27EF3BCC2AF8
#define C879098C_893D_4CA3_B58B_27EF3BCC2AF8

#include "raylib.h"
#include <vector>
#include <utility> // Para std::pair
#include "bumper.h" // Inclua o cabeçalho do bumper aqui

using std::vector;
using std::pair;

// Estrutura para definir uma fase completa
struct GamePhase {
    std::vector<std::pair<Vector2, Vector2>> walls;
    std::vector<Bumper> bumpers;
    Vector2 initialBallPosition; // Posição inicial da bola para esta fase
};

// Declarações externas das fases completas
extern GamePhase p1_phase_data; // Usando um novo nome para evitar conflito com p1_walls
extern GamePhase p2_phase_data; // Usando um novo nome

#endif
