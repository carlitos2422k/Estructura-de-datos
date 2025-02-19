# Nombre del ejecutable
TARGET = programa

# Compilador
CC = g++

# Archivos fuente
SRCS = main.cpp Grafo.cpp

# Flags de compilación
CFLAGS = -I"C:/MinGW/include"
LDFLAGS = -L"C:/MinGW/lib" -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

# Regla principal
$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Limpiar archivos generados
clean:
	del $(TARGET).exe
