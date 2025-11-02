CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

OBJS = simulation.o adaptive.o trapezoid.o

sim: $(OBJS)
	$(CXX) $(CXXFLAGS) -o sim $(OBJS)

simulation.o: simulation.cpp adaptive.h trapezoid.h
	$(CXX) $(CXXFLAGS) -c simulation.cpp

adaptive.o: adaptive.cpp adaptive.h
	$(CXX) $(CXXFLAGS) -c adaptive.cpp

trapezoid.o: trapezoid.cpp trapezoid.h
	$(CXX) $(CXXFLAGS) -c trapezoid.cpp

clean:
	rm -f *o sim