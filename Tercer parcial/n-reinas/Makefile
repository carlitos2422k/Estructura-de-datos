# Compiler settings
CXX = g++
CXXFLAGS = -Wall -std=c++11

# SDL2 settings
SDL_INCLUDE = -IC:/MinGW/include/SDL2
SDL_LIB = -LC:/MinGW/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# Project files
SRCS = main.cpp reinas.cpp graphics.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = reinas.h graphics.h
TARGET = nqueens.exe

# Detect OS
ifeq ($(OS),Windows_NT)
    RM = del /Q
    CLEAN_TARGET = $(subst /,\,$(TARGET))
    CLEAN_OBJS = $(subst /,\,$(OBJS))
else
    RM = rm -f
    CLEAN_TARGET = $(TARGET)
    CLEAN_OBJS = $(OBJS)
endif

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(SDL_LIB)

# Compile
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(SDL_INCLUDE) -c $< -o $@

# Copy DLLs (Windows only)
.PHONY: copy_dlls
copy_dlls:
ifeq ($(OS),Windows_NT)
	copy "C:\MinGW\bin\SDL2.dll" .
	copy "C:\MinGW\bin\SDL2_image.dll" .
	copy "C:\MinGW\bin\libpng16-16.dll" .
	copy "C:\MinGW\bin\zlib1.dll" .
endif

# Clean
.PHONY: clean
clean:
	$(RM) $(CLEAN_OBJS) $(CLEAN_TARGET)

# Full build including DLL copy
.PHONY: full
full: all copy_dlls