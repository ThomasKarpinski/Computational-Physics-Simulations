CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc

SRC_CPP_FILES = src/main.cpp src/simulation.cpp src/potentials.cpp src/integrator.cpp
OBJ_FILES = $(patsubst src/%.cpp, build/%.o, $(SRC_CPP_FILES))

TARGET = build/md_simulation

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o $(TARGET)

.PHONY: all clean

.PHONY: all clean
