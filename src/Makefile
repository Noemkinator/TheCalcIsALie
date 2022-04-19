CXX=g++
CPPFLAGS=-g -O2
CALCSOURCES=$(wildcard *.cpp *.h *.ui)
BIN = TheCalcIsALie profiling
.PHONY: pack run clean

%.o: %.cpp %.h
	$(CXX) -c $(CPPFLAGS) $< -o $@

all: $(BIN)

TheCalcIsALie: $(CALCSOURCES)
	cmake -S . -B build
	cd build && make
	cp ./build/TheCalcIsALie ./

profiling: profiling.o calc.o
	$(CXX) $(CPPFLAGS) -o $@ $^

pack:
	zip xzajic22_xsocha02_xtrutn00_xpuchn02.zip *.cpp *.h *.ui CMakeLists.txt Makefile Doxyfile

run: TheCalcIsALie
	./TheCalcIsALie

clean:
	rm -rf *.o ./build ./test/build ./calc_tests $(BIN)

calc_tests: tdd_tests.cpp calc.cpp
	cmake -S test -B test/build
	cd test/build && make
	cp ./test/calc_tests ./

test: calc_tests
	./calc_tests

doc:
	doxygen ./Doxyfile