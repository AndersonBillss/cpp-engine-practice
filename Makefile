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
SUB_DIR = ctx
OUT_DIR = output

SHADER_DIR = $(SRC_DIR)/shaders
ASSET_DIR = $(SRC_DIR)/assets
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin


SRC_SHADER_DIR = $(SHADER_DIR)
BIN_SHADER_DIR = $(BIN_DIR)/$(SHADER_DIR)
SRC_ASSET_DIR = $(ASSET_DIR)
BIN_ASSET_DIR = $(BIN_DIR)/$(ASSET_DIR)

SRC = $(foreach folder, $(SUB_DIR), $(wildcard $(SRC_DIR)/$(folder)/*.cpp))
SRC += $(wildcard $(SRC_DIR)/*.cpp)

OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: build run

# Run the executable
run: build
	@echo "Running $(TARGET)..."
	$(BIN_DIR)/$(TARGET)$(EXE_SUFFIX)

# Build the executable
build: $(OUT_DIR) $(BIN_DIR) $(SUB_DIR) $(OBJ) copy_shaders copy_assets
	$(CXX) -o $(BIN_DIR)/$(TARGET)$(EXE_SUFFIX) $(OBJ) $(BINFLAGS)

# Compile C++ files to .o files inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(OBJFLAGS) -c $< -o $@

# Ensure subdirectories exist
$(SUB_DIR): $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$@
# Ensure directories exist
$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR)/

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Copy GLSL shaders to bin/
copy_shaders: $(BIN_SHADER_DIR)
	cp $(SRC_SHADER_DIR)/*.glsl $(BIN_SHADER_DIR)/

$(BIN_SHADER_DIR):
	mkdir -p $(BIN_SHADER_DIR)

copy_assets: $(BIN_ASSET_DIR)
	cp $(SRC_ASSET_DIR)/* $(BIN_ASSET_DIR)/

$(BIN_ASSET_DIR):
	mkdir -p $(BIN_ASSET_DIR)

# Clean compiled files but keep directories
clean:
	rm -rf $(OUT_DIR)