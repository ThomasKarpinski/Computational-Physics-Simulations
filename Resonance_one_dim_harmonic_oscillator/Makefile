CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

OBJS = main.o rk4.o ode.o

all: sim

sim: $(OBJS)
	$(CXX) $(CXXFLAGS) -o sim $(OBJS)

main.o: main.cpp rk4.h ode.h
	$(CXX) $(CXXFLAGS) -c main.cpp

rk4.o: rk4.cpp rk4.h ode.h
	$(CXX) $(CXXFLAGS) -c rk4.cpp

ode.o: ode.cpp ode.h
	$(CXX) $(CXXFLAGS) -c ode.cpp

clean:
	rm -f *.o sim output.csv
