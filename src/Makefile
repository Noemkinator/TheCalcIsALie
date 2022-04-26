# Makefile needs to be run within a Qt MinGW shell to correctly set the PATH enviromental variable
CXX=g++
CPPFLAGS=-g -O2
CALCSOURCES=$(wildcard *.cpp *.h *.ui)
BIN = bin\TheCalcIsALie.exe stddev.exe
.PHONY: pack run clean

%.o: %.cpp %.h
	$(CXX) -c $(CPPFLAGS) $< -o $@

all: $(BIN)

bin\TheCalcIsALie.exe: $(CALCSOURCES)
	cmake -G "Unix Makefiles" -S . -B build
	cd build && make
	if not exist "bin" mkdir bin
	move build\TheCalcIsALie.exe .\bin\TheCalcIsALie.exe
	windeployqt .\bin\TheCalcIsALie.exe

stddev.exe: profiling.o calc.o
	$(CXX) $(CPPFLAGS) -o $@ $^

pack: xzajic22_xsocha02_xtrutn00_xpuchn02.zip

xzajic22_xsocha02_xtrutn00_xpuchn02.zip:
	zip -j $@ *.cpp *.h *.ui CMakeLists.txt Makefile Doxyfile ..\hodnoceni.txt ..\dokumentace.pdf ..\odevzdani.txt
	zip $@ test\CMakeLists.txt

run: bin\TheCalcIsALie.exe
	$<

clean:
	del /s /q *.o calc_tests.exe $(BIN)
	if exist "build" rd /s /q "build"
	if exist "bin" rd /s /q "bin"
	if exist "test\build" rd /s /q "test\build"

calc_tests.exe:
	cmake -G "Unix Makefiles" -S test -B test\build
	cd test/build && make
	move .\test\calc_tests.exe .

test: calc_tests.exe
	$<

# may not work on Windows based systems - Doxygen needs to be installed
doc:
	doxygen .\Doxyfile
