# Nombre del ejecutable
TARGET = main

# Compilador
CXX = g++

# Flags del compilador
CXXFLAGS = -Wall -std=c++11

# Archivos fuente y sus objetos
SRCS = ArbolAVL.cpp HashUsuario.cpp Libro.cpp mainbase.cpp MenuManager.cpp Prestamo.cpp PrestamoManager.cpp Usuario.cpp DatabaseManager.cpp RecomendacionManager.cpp Validacion.cpp
OBJS = $(SRCS:.cpp=.o)

# Regla para compilar el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar los archivos fuente en objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Regla para ejecutar el programa después de compilar
run: $(TARGET)
	./$(TARGET)
