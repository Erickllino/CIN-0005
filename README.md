

# SpaceBall Odyssey

Um jogo de pinball feito em C++ com Raylib, onde você compete contra aliens para decidir o futuro do mundo! Inspirado em clássicos de pinball, com fases, personagens jogáveis e sistema de leaderboard.

## 🕹️ Como Jogar

- **Q**: Aciona o fliper esquerdo
- **E**: Aciona o fliper direito
- **D**: Aciona o poder do personagem
- **Setas**: Controla a bola (com personagens específicas)
- **Menu**: Navegue usando o Mouse

## 📖 História

Aliens invadiram a Terra e desafiaram a humanidade para um torneio de pinball. O vencedor se tornará presidente do mundo! Vença fases, derrote chefes e mostre suas habilidades.

## 🚩 Funcionalidades

- Sistema de flipers realista (com física, força e cor dinâmica)
- Fases com diferentes obstáculos e paredes
- Personagens jogáveis com habilidades
- Leaderboard por fase
- Cinemáticas de história
- Efeitos sonoros e sprites personalizados


## 📦 Estrutura do Código

```
src/           # Código-fonte principal do jogo (C++)
│   ├─ main.cpp        # Ponto de entrada do jogo, inicialização da janela e loop principal
│   ├─ game.cpp        # Lógica central do jogo, estados, fases, placar
│   ├─ player.cpp      # Implementação do jogador e movimentação da bola
│   ├─ bumper.cpp      # Lógica dos bumpers (alvos de pontuação)
│   ├─ fases.cpp       # Definição das fases, paredes e obstáculos
│   └─ utility.cpp     # Funções utilitárias

include/      # Headers (interfaces das classes e structs)
│   ├─ game.h
│   ├─ player.h
│   ├─ bumper.h
│   ├─ fases.h
│   └─ utility.h

assets/
│   ├─ images/         # Sprites, imagens dos personagens, mapas
│   └─ sounds/         # Efeitos sonoros do jogo

external/raylib/       # Biblioteca Raylib (precisa ser compilada manualmente)
Map_editor/            # Editor de mapas em Python (ferramenta auxiliar)
Makefile               # Script de build principal do projeto
README.md              # Este arquivo
FLIPERS.md             # Detalhes técnicos do sistema de flipers
Organize_project.txt   # Planejamento e divisão de tarefas
```

## 🛠️ Instalação e Execução

### Pré-requisitos (Linux)
Instale as dependências do sistema:
```bash
sudo apt update
sudo apt install build-essential git cmake libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
```

### Passo a passo
1. **Clone o repositório:**
	```bash
	git clone https://github.com/Erickllino/CIN-0005 --recursive
	cd CIN-0005
	```
2. **Compile a Raylib:**
	```bash
	cd external/raylib/src
	make
	cd ../../..
	```
3. **Compile o projeto:**
	```bash
	make
	```
4. **Execute o jogo:**
	```bash
	./main
	```

#### Rodando em máquina virtual
Se não estiver em Linux, use uma VM (ex: Ubuntu). Habilite "Shared Clipboard Bidirectional" e "Enable 3D Acceleration" nas configurações da VM. Veja exemplos de configuração em: [vídeo 1](https://www.youtube.com/watch?v=Hva8lsV2nTk&t=66s) e [vídeo 2](https://www.youtube.com/watch?v=sAMnXte56yY).

## 👾 Personagens

- Eitor (JoaoPintoBall): Pega ball
- Jessica (Jessball): Score ball
- Heiji (LeBall): Trava ball
- Erick, Samira, Ivan: outros personagens

## 🏆 Fases e Objetivos

- Fases com obstáculos, bumpers e coletáveis
- Boss fight em fases avançadas
- Pontuação por acertos e progressão por leaderboard

## 🎮 Sistema de Flipers

O jogo possui flipers controlados por Q/E, com física realista, força extra ao acionar, cor dinâmica e som de colisão. Veja detalhes técnicos em `FLIPERS.md`.



## 👨‍💻 Autores

- Ivan, Heiji, Jessica, Tutubas, Heitor, Samira, Erick
- Contribuições: Cinemática, lógica dos bumpers/flipers, mapas, leaderboard, personagens



