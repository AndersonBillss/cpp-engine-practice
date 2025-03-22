# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lglew32 -lglfw3 -lopengl32 -Iinclude -Wall

# Executable Name
TARGET = engine
EXE_SUFFIX := .exe

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: build run

# Run the executable
run: build
	@echo "Running $(TARGET)..."
	$(BIN_DIR)/$(TARGET)$(EXE_SUFFIX)

# Build the executable
build: $(BIN_DIR) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)/$(TARGET)$(EXE_SUFFIX) $(OBJ)

# Compile C++ files to .o files inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure directories exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean compiled files but keep directories
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)