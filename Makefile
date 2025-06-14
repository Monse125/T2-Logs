# Makefile para la Tarea 2 - Algoritmo de Kruskal (Versión Organizada)

# Configuración del compilador
CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Iinclude
TARGET = kruskal
ANALYZER = analyzer

# Directorios
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
DATA_DIR = data
SCRIPTS_DIR = scripts

# Archivos fuente
MAIN_SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/node.cpp $(SRC_DIR)/edge.cpp $(SRC_DIR)/union_find.cpp $(SRC_DIR)/graph_generator.cpp $(SRC_DIR)/kruskal.cpp $(SRC_DIR)/experiment.cpp
MAIN_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MAIN_SOURCES))

ANALYZER_SOURCE = $(SRC_DIR)/analyzer.cpp
ANALYZER_OBJECT = $(BUILD_DIR)/analyzer.o

.PHONY: all clean run analyze help modular original setup

# Compilar versión modular (por defecto)
all: setup modular

# Crear directorios necesarios
setup:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(DATA_DIR)

# Versión modular
modular: setup $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(ANALYZER)
	@echo "Versión modular compilada exitosamente"

# Versión original (un solo archivo)
original: setup
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(SRC_DIR)/main_original.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(ANALYZER) $(ANALYZER_SOURCE)
	@echo "Versión original compilada exitosamente"

# Compilar programa principal modular
$(BUILD_DIR)/$(TARGET): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar analizador
$(BUILD_DIR)/$(ANALYZER): $(ANALYZER_OBJECT)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regla para compilar archivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecutar los experimentos
run: $(BUILD_DIR)/$(TARGET)
	cd $(DATA_DIR) && ../$(BUILD_DIR)/$(TARGET)

# Analizar resultados
analyze: $(BUILD_DIR)/$(ANALYZER)
	cd $(DATA_DIR) && ../$(BUILD_DIR)/$(ANALYZER)

# Compilar y ejecutar todo el experimento
experiment: modular run analyze

# Validar el proyecto
validate: modular
	@echo "Ejecutando validación del proyecto..."
	@chmod +x $(SCRIPTS_DIR)/validate.sh
	@$(SCRIPTS_DIR)/validate.sh

# Limpiar archivos generados
clean:
	rm -rf $(BUILD_DIR)/*
	rm -f $(DATA_DIR)/results.txt
	rm -f $(DATA_DIR)/*.png

# Limpiar todo incluyendo directorios
clean-all: clean
	rm -rf $(BUILD_DIR)

# Mostrar ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make            - Compilar versión modular"
	@echo "  make modular    - Compilar versión modular"
	@echo "  make original   - Compilar versión original (un archivo)"
	@echo "  make run        - Ejecutar experimentos"
	@echo "  make analyze    - Analizar resultados"
	@echo "  make experiment - Compilar, ejecutar y analizar"
	@echo "  make validate   - Validar el proyecto completo"
	@echo "  make clean      - Limpiar archivos generados"
	@echo "  make clean-all  - Limpiar todo incluyendo directorios"
	@echo "  make help       - Mostrar esta ayuda"
	@echo ""
	@echo "Estructura del proyecto:"
	@echo "  src/       - Código fuente (.cpp)"
	@echo "  include/   - Headers (.h)"
	@echo "  build/     - Ejecutables compilados"
	@echo "  data/      - Datos y resultados"
	@echo "  scripts/   - Scripts de utilidad"
	@echo "  docs/      - Documentación"

# Dependencias de archivos header
$(BUILD_DIR)/node.o: $(INCLUDE_DIR)/node.h
$(BUILD_DIR)/edge.o: $(INCLUDE_DIR)/edge.h $(INCLUDE_DIR)/node.h
$(BUILD_DIR)/union_find.o: $(INCLUDE_DIR)/union_find.h $(INCLUDE_DIR)/node.h
$(BUILD_DIR)/graph_generator.o: $(INCLUDE_DIR)/graph_generator.h $(INCLUDE_DIR)/node.h $(INCLUDE_DIR)/edge.h
$(BUILD_DIR)/kruskal.o: $(INCLUDE_DIR)/kruskal.h $(INCLUDE_DIR)/node.h $(INCLUDE_DIR)/edge.h $(INCLUDE_DIR)/union_find.h $(INCLUDE_DIR)/graph_generator.h
$(BUILD_DIR)/experiment.o: $(INCLUDE_DIR)/experiment.h $(INCLUDE_DIR)/kruskal.h $(INCLUDE_DIR)/graph_generator.h
$(BUILD_DIR)/main.o: $(INCLUDE_DIR)/experiment.h
$(BUILD_DIR)/analyzer.o: $(SRC_DIR)/analyzer.cpp
