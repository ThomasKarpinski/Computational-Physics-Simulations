CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

OBJS = main.o sympletic.o

sim: $(OBJS)
	$(CXX) $(CXXFLAGS) -o sim $(OBJS)

main.o: main.cpp sympletic.h
	$(CXX) $(CXXFLAGS) -c main.cpp

sympletic.o: sympletic.cpp sympletic.h
	$(CXX) $(CXXFLAGS) -c sympletic.cpp

clean:
	rm -f *o sim