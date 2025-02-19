# Variables del compilador y opciones
CXX = g++
CXXFLAGS = -Wall

# Archivos fuente y ejecutable
SRC = main.cpp HashTable.cpp
TARGET = main

# Regla principal para compilar
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Limpieza de archivos generados
clean:
	rm -f $(TARGET)

.PHONY: all clean
