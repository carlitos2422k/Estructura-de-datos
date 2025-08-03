# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = .

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable name
EXEC = $(BIN_DIR)/sfml-graph

# Main targets
all: create_dirs $(EXEC)

# Create necessary directories
create_dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# Link
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(SFML_LIBS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR)
	rm -f $(EXEC)

# Clean and rebuild
rebuild: clean all

.PHONY: all clean rebuild create_dirs