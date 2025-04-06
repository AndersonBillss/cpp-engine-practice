# Compiler
CXX = g++

# Compiler Flags
OBJFLAGS = -IC:/msys64/mingw64/include -Iinclude -Wall
BINFLAGS = -LC:/msys64/mingw64/lib -lglew32 -lglfw3 -lopengl32

# Executable Name
TARGET = engine
EXE_SUFFIX := .exe

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SHADER_DIR = $(SRC_DIR)/shaders
BIN_SHADER_DIR = $(BIN_DIR)/shaders
ASSET_DIR = $(SRC_DIR)/assets
BIN_ASSET_DIR = $(BIN_DIR)/assets

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: build run

# Run the executable
run: build
	@echo "Running $(TARGET)..."
	$(BIN_DIR)/$(TARGET)$(EXE_SUFFIX)

# Build the executable
build: $(BIN_DIR) $(OBJ) copy_shaders copy_assets
	$(CXX) -o $(BIN_DIR)/$(TARGET)$(EXE_SUFFIX) $(OBJ) $(BINFLAGS)

# Compile C++ files to .o files inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(OBJFLAGS) -c $< -o $@

# Ensure directories exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

# Copy GLSL shaders to bin/
copy_shaders: $(BIN_SHADER_DIR)
	cp $(SHADER_DIR)/*.glsl $(BIN_SHADER_DIR)/

$(BIN_SHADER_DIR):
	mkdir -p $(BIN_SHADER_DIR)

copy_assets: $(BIN_ASSET_DIR)
	cp $(ASSET_DIR)/* $(BIN_ASSET_DIR)/

$(BIN_ASSET_DIR):
	mkdir -p $(BIN_ASSET_DIR)

# Clean compiled files but keep directories
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)