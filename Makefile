# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -Wall -std=c++17

# Nome do executável
TARGET = sistema_supermercado

# Diretório dos arquivos fonte
SRC_DIR = src

# Diretório de build (para arquivos objeto e executável)
BUILD_DIR = build

# Arquivos fonte
SRCS = $(SRC_DIR)/CAIXA.cpp $(SRC_DIR)/CLIENTE.cpp $(SRC_DIR)/main.cpp

# Arquivos objeto (gerados a partir dos arquivos fonte)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Regra padrão
all: $(BUILD_DIR)/$(TARGET)
	cp $(BUILD_DIR)/$(TARGET) .  # Copia o executável para o diretório atual

# Regra para compilar o executável
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Regra para compilar cada arquivo fonte em um arquivo objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)  # Cria o diretório build se não existir
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rodar o programa
run: all
	./$(TARGET)

# Para evitar conflitos com arquivos chamados "clean" ou "run"
.PHONY: clean run