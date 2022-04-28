# Makefile needs to be run within a Qt MinGW shell to correctly set the PATH enviromental variable
SHELL=cmd
CXX=g++
CPPFLAGS=-g -O2
CALCLIB=$(wildcard calc.*)
CALCSOURCES=$(wildcard *.cpp *.h *.ui)
BIN = bin\TheCalcIsALie.exe stddev.exe
.PHONY: all pack run clean test doc

all: $(BIN)

%.o: %.cpp %.h
	$(CXX) -c $(CPPFLAGS) $< -o $@

bin\TheCalcIsALie.exe: $(CALCSOURCES)
	cmake -G "Unix Makefiles" -S . -B build
	cd build && make
	if not exist "bin" mkdir bin
	cmd /C move build\TheCalcIsALie.exe bin
	windeployqt $@
	if exist "..\dokumentace.pdf" copy "..\dokumentace.pdf" bin
	if exist "dokumentace.pdf" copy "dokumentace.pdf" bin

stddev.exe: profiling.o calc.o
	$(CXX) $(CPPFLAGS) -o $@ $^

pack: xzajic22_xsocha02_xtrutn00_xpuchn02.zip

xzajic22_xsocha02_xtrutn00_xpuchn02.zip:
	zip -j $@ *.cpp *.h *.ui *.rc *.ico CMakeLists.txt Makefile Doxyfile ..\hodnoceni.txt ..\dokumentace.pdf ..\odevzdani.txt
	zip $@ test\CMakeLists.txt

run: bin\TheCalcIsALie.exe
	$<

clean:
	del /s /q /Q *.o calc_test.exe stddev.exe
	if exist "build" rd /s /q "build"
	if exist "bin" rd /s /q "bin"
	if exist "test\build" rd /s /q "test\build"
	if exist "docs" rd /s /q "docs"

calc_test.exe: tdd_tests.cpp $(CALCLIB)
	cmake -G "Unix Makefiles" -S test -B test\build
	cd test\build && make
	cmd /C move .\test\build\$@

test: calc_test.exe
	$<

# may not work on Windows based systems - Doxygen needs to be installed
doc:
	doxygen Doxyfile
