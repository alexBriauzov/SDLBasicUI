# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I../src -I../src/UI -Iinclude/SDL2 -Iinclude 

# Directories
SRC_DIR := ../src
BUILD_DIR := build

# List subdirectories manually
SRC_SUBDIRS := $(SRC_DIR) $(SRC_DIR)/UI

# Gather all .cpp source files
SOURCES := $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.cpp))

# Map source files to object files (mirror directory structure under build/)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# SDL2 linking
SDL2_LIB := lib
LDFLAGS := -L$(SDL2_LIB) -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

# Output binary
TARGET := main

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile each .cpp to its corresponding .o in build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
