# Makefile multiplataforma: Linux/macOS e Windows (MinGW)

# Compiladores
CC          := g++

# Flags de compilação comuns
CFLAGS      := -I./include -I./external/raylib/src

# Flags de link para cada plataforma
LDFLAGS_LIN := -Lexternal/raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Diretórios fonte e build
SRC_DIR       := src
BUILD_DIR     := build

# Fontes e objetos
SRCS       := $(wildcard $(SRC_DIR)/*.cpp)
OBJS       := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Alvos finais
TARGET         := main

# Alvo padrão: compila para Linux/macOS
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS_LIN)

# Regra para objetos Linux/macOS
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
