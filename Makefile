

# Compilador
CC          := g++

# Detecção do sistema operacional
UNAME_S := $(shell uname -s)

# Flags de compilação comuns
CFLAGS      := -I./include -I./external/raylib/src

# Flags de link específicas por plataforma
ifeq ($(UNAME_S),Linux)
    LDFLAGS := -Lexternal/raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif
ifeq ($(UNAME_S),Darwin)
    LDFLAGS := -Lexternal/raylib/src -lraylib -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif

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
	$(CC) $^ -o $@ $(LDFLAGS)

# Regra para objetos (Linux/macOS compatível)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Informações do sistema
info:
	@echo "Sistema detectado: $(UNAME_S)"
	@echo "Compilador: $(CC)"
	@echo "Flags de link: $(LDFLAGS)"

.PHONY: all clean info
