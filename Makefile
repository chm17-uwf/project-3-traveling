CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -ftest-coverage -fprofile-arcs

SRCS = $(wildcard *.hpp)
OBJECTS = $(SRCS:%.hpp=%.o)

main: $(OBJECTS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf main.dSYM
	$(RM) *.o *.gc* test/*.o test/*.gc* *.dSYM test/test core main
