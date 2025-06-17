# Makefile para Tarea 2 - Algoritmo de Kruskal
# CC4102 - Diseño y Análisis de Algoritmos

# Configuración del compilador
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
INCLUDES = -I./include

# Directorios
SRCDIR = src
OBJDIR = build
INCDIR = include

# Archivos fuente
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Ejecutables
MAIN_EXPERIMENT = kruskal_experiment
MAIN_SIMPLE = kruskal_test

# Regla por defecto
all: $(MAIN_EXPERIMENT) $(MAIN_SIMPLE)

# Crear el ejecutable principal (experimento completo)
$(MAIN_EXPERIMENT): main.cpp $(OBJECTS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) main.cpp $(OBJECTS) -o $@
	@echo "✅ Experimento completo compilado: ./$(MAIN_EXPERIMENT)"

# Crear el ejecutable de prueba simple
$(MAIN_SIMPLE): main_simple.cpp $(OBJECTS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) main_simple.cpp $(OBJECTS) -o $@
	@echo "✅ Prueba simple compilada: ./$(MAIN_SIMPLE)"

# Compilar archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Crear directorio de objetos si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Ejecutar experimento completo
run-experiment: $(MAIN_EXPERIMENT)
	@echo "🚀 Ejecutando experimento completo..."
	./$(MAIN_EXPERIMENT)

# Ejecutar prueba simple
run-test: $(MAIN_SIMPLE)
	@echo "🧪 Ejecutando prueba simple..."
	./$(MAIN_SIMPLE)

# Limpiar archivos compilados
clean:
	@echo "🧹 Limpiando archivos compilados..."
	rm -rf $(OBJDIR)
	rm -f $(MAIN_EXPERIMENT) $(MAIN_SIMPLE)
	rm -f results.csv
	rm -f *.o *.exe *.out
	rm -f core core.*
	rm -f .DS_Store
	@echo "✅ Limpieza completada"

# Limpiar solo ejecutables (mantener objetos)
clean-exe:
	@echo "🗑️  Eliminando ejecutables..."
	rm -f $(MAIN_EXPERIMENT) $(MAIN_SIMPLE)
	rm -f *.exe *.out
	@echo "✅ Ejecutables eliminados"

# Limpiar todo incluyendo archivos de distribución
clean-all: clean
	@echo "🗑️  Limpieza profunda..."
	rm -f *.tar.gz *.zip
	rm -f *.log *.tmp
	find . -name "*~" -delete 2>/dev/null || true
	find . -name "*.bak" -delete 2>/dev/null || true
	@echo "✅ Limpieza profunda completada"

# Recompilar todo desde cero
rebuild: clean all

# Mostrar información del proyecto
info:
	@echo "📋 INFORMACIÓN DEL PROYECTO"
	@echo "Compilador: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Archivos fuente: $(SOURCES)"
	@echo "Archivos objeto: $(OBJECTS)"
	@echo "Ejecutables: $(MAIN_EXPERIMENT), $(MAIN_SIMPLE)"

# Verificar dependencias y estructura
check:
	@echo "🔍 VERIFICANDO ESTRUCTURA DEL PROYECTO..."
	@test -d $(INCDIR) || (echo "❌ Directorio include/ no encontrado" && exit 1)
	@test -d $(SRCDIR) || (echo "❌ Directorio src/ no encontrado" && exit 1)
	@test -f main.cpp || (echo "❌ main.cpp no encontrado" && exit 1)
	@test -f main_simple.cpp || (echo "❌ main_simple.cpp no encontrado" && exit 1)
	@echo "✅ Estructura del proyecto correcta"

# Crear un archivo de distribución (para entrega)
dist: clean
	@echo "📦 Creando archivo de distribución..."
	tar -czf tarea2-kruskal.tar.gz \
		$(INCDIR)/ $(SRCDIR)/ \
		main.cpp main_simple.cpp \
		Makefile README.md
	@echo "✅ Archivo tarea2-kruskal.tar.gz creado"

# Ayuda
help:
	@echo "📚 COMANDOS DISPONIBLES:"
	@echo "  make              - Compilar ambos ejecutables"
	@echo "  make run-experiment - Compilar y ejecutar experimento completo"
	@echo "  make run-test     - Compilar y ejecutar prueba simple"
	@echo "  make clean        - Limpiar archivos compilados y resultados"
	@echo "  make clean-exe    - Limpiar solo ejecutables"
	@echo "  make clean-all    - Limpieza profunda (incluye archivos temporales)"
	@echo "  make rebuild      - Limpiar y recompilar todo"
	@echo "  make info         - Mostrar información del proyecto"
	@echo "  make check        - Verificar estructura del proyecto"
	@echo "  make dist         - Crear archivo de distribución"
	@echo "  make help         - Mostrar esta ayuda"

# Marcar reglas que no son archivos
.PHONY: all run-experiment run-test clean clean-exe clean-all rebuild info check dist help
