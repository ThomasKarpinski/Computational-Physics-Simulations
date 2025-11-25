CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
LDFLAGS =
SOURCES = src/main.cpp
EXECUTABLE = heat_diffusion

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE) *.txt *.png
