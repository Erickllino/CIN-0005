# Setup instructions

### 1o - Clone o repositório
```bash
git clone https://github.com/Erickllino/CIN-0005 --recursive
```
### 2o - Compile o raylib
```bash
cd external/raylib/src
make
```

### 3o - Compile o projeto
```bash
# Volte para a pasta do projeto e digite o comando
make
```

### 4o - Rode
```bash
./main
```
### Caso nao tenha sistema linux disponivel 
Use uma maquina virtual https://www.youtube.com/watch?v=Hva8lsV2nTk&t=66s (video usa ubuntu)
apos criar a maquina virtual va em settings e habilite Shared Clipboard Bidirectional pra facilitar sua vida na aba General e Enable 3D Acceleration para que o ambiente possa usar a gpu do proprio computador. https://www.youtube.com/watch?v=sAMnXte56yY (video usa o kali, mas mostra as configuracoes do virtualbox). Com a maquina virtual configurada e iniciada, abra o terminal e instale as dependencias
```bash
sudo apt update
sudo apt install build-essential git
sudo apt install cmake
sudo apt install libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
sudo apt install libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libglu1-mesa-dev
```



