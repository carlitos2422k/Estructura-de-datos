# Makefile para el juego de Tetris con letras
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Archivos fuente
SOURCES = main.cpp LetterGame.cpp Point.cpp Cell.cpp

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nombre del ejecutable
EXECUTABLE = letter_tetris

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@

# Regla para compilar archivos .cpp a .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencias específicas
main.o: main.cpp LetterGame.h
LetterGame.o: LetterGame.cpp LetterGame.h DoublyLinkedList.h Cell.h Point.h Node.h
Cell.o: Cell.cpp Cell.h Point.h
Point.o: Point.cpp Point.h

# Limpiar archivos compilados
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Ejecutar el programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Para compilar en Windows con MSYS2
windows:
	g++ -o letter_tetris.exe $(SOURCES) -lwinmm