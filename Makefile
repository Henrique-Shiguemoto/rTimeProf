COMPILER=gcc
COMPILER_CPP=g++
SRC=main.c rTimeProf.c
SRC_CPP=main.cpp rTimeProf.cpp
BIN=main
COMPILER_FLAGS=-Wall -Wextra -g -std=c11
COMPILER_FLAGS_CPP=-Wall -Wextra -g -std=c++11
DEBUGGER=gdb

all:
	$(COMPILER) $(COMPILER_FLAGS) $(SRC) -o $(BIN)

cpp:
	$(COMPILER_CPP) $(COMPILER_FLAGS_CPP) $(SRC_CPP) -o $(BIN)

run:
	$(BIN)

debug:
	$(DEBUGGER) $(BIN)

every: clean all run

every_cpp: clean cpp run

every_debug: clean all debug

every_debug_cpp: clean all debug

clean:
	del *.o *.exe