# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++17 -I../src -I../src/UI -Iinclude/SDL2 -Iinclude 

# Directories
SRC_DIR := ../src
BUILD_DIR := build

# Manually list known subdirectories if recursive wildcard is not supported
SRC_SUBDIRS := $(SRC_DIR) $(SRC_DIR)/UI  # Add more as needed

# Collect all .cpp files from the known subdirectories
SOURCES := $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.cpp))

# Convert to .o paths in build dir
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

SDL2_LIB := lib

LDFLAGS := -L$(SDL2_LIB) -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

# Target binary
TARGET := main.exe

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compilation rule (Windows mkdir)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	@if exist "$(TARGET)" del /Q "$(TARGET)"
