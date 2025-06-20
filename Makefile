# Compiler
CXX = g++

# Compiler Flags
# OBJFLAGS = -IC:/msys64/mingw64/include -Iinclude -Wall
# BINFLAGS = -LC:/msys64/mingw64/lib -lglew32 -lglfw3 -lopengl32
CXX_FLAGS = -LC:/msys64/mingw64/lib -lglew32 -lglfw3 -lopengl32 -IC:/msys64/mingw64/include -Iinclude -Wall

# Executable Name
TARGET = engine
EXE_SUFFIX = .exe

# Directories
SRC_DIR = src
ASSET_DIR = assets
SRC_FILES = $(shell find $(SRC_DIR) -name '*.cpp')

BUILD_DIR = obj
DIST_DIR = dist

OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
DEP := $(OBJ:.o=.d)

all: build run

run: build
	@echo "Running $(TARGET)..."
	$(DIST_DIR)/$(TARGET)$(EXE_SUFFIX)

# Build the executable
build: prepare_build_dirs $(OBJ) $(DIST_DIR) copy_assets
	$(CXX) -o $(DIST_DIR)/$(TARGET)$(EXE_SUFFIX) $(OBJ) $(CXX_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

copy_assets: $(DIST_DIR)
	mkdir -p $(DIST_DIR)/$(ASSET_DIR)
	cp -r $(ASSET_DIR)/* $(DIST_DIR)/$(ASSET_DIR)/

$(DIST_DIR):
	mkdir -p $(DIST_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%/:
	mkdir -p $@

prepare_build_dirs:
	mkdir -p $(sort $(dir $(OBJ)))

# Clean compiled files but keep directories
clean:
	rm -rf $(DIST_DIR)
	rm -rf $(BUILD_DIR)