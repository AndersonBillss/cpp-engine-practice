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
	$(CXX) -o $(BIN_DIR)/$(TARGET)$(EXE_SUFFIX) $(OBJ) $(BINFLAGS)

# Compile C++ files to .o files inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(OBJFLAGS) -c $< -o $@

# Ensure directories exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR) 2> NUL || true

$(BIN_DIR):
	mkdir $(BIN_DIR) 2> NUL || true

# Clean compiled files but keep directories
clean:
	if exist $(OBJ_DIR) rmdir /s /q $(OBJ_DIR)
	if exist $(BIN_DIR) rmdir /s /q $(BIN_DIR)