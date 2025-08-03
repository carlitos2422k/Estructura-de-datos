# Makefile para Juego de Letras

# Compilador
CXX = g++

# Banderas de compilacion
CXXFLAGS = -std=c++11 -Wall -Wextra

# Nombre del ejecutable
TARGET = juego_letras

# Archivos de codigo fuente
SOURCES = main.cpp JuegoLetras.cpp Punto.cpp Celda.cpp

# Archivos de encabezado
HEADERS = JuegoLetras.h Punto.h Celda.h Nodo.h ListaDoblementeEnlazada.h

# Archivos objeto (generados a partir de los fuentes)
OBJECTS = $(SOURCES:.cpp=.o)

# Regla por defecto
all: $(TARGET)

# Regla para crear el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -luser32

# Regla generica para compilar archivos .cpp a .o
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Reconstruir todo
rebuild: clean all

# Ejecutar el juego
run: $(TARGET)
	./$(TARGET)

# Phony targets (targets que no son archivos)
.PHONY: all clean rebuild run