# Makefile multiplataforma: Linux/macOS e Windows (MinGW)

# Compiladores
CC          := g++
CC_WIN      := x86_64-w64-mingw32-g++

# Flags de compilação comuns
CFLAGS      := -I./include -I./external/raylib/src

# Flags de link para cada plataforma
LDFLAGS_LIN := -Lexternal/raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LDFLAGS_WIN := -Lexternal/raylib/src -lraylib -lopengl32 -lwinmm -lgdi32 -lole32 -luuid -lws2_32

# Diretórios fonte e build
SRC_DIR       := src
BUILD_DIR     := build
BUILD_DIR_WIN := build_win

# Fontes e objetos
SRCS       := $(wildcard $(SRC_DIR)/*.cpp)
OBJS       := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
OBJS_WIN   := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR_WIN)/%.o,$(SRCS))

# Alvos finais
TARGET         := main
TARGET_WIN     := main.exe

.PHONY: all windows clean

# Alvo padrão: compila para Linux/macOS
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS_LIN)

# Regra para objetos Linux/macOS
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilação para Windows via MinGW
windows: $(BUILD_DIR_WIN) $(TARGET_WIN)

$(TARGET_WIN): $(OBJS_WIN)
	$(CC_WIN) $^ -o $@ $(LDFLAGS_WIN)

# Regra para objetos Windows
$(BUILD_DIR_WIN)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR_WIN)
	$(CC_WIN) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR_WIN):
	mkdir -p $(BUILD_DIR_WIN)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(BUILD_DIR_WIN) $(TARGET) $(TARGET_WIN)
