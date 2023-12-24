COMPILER=gcc
SRC=main.c rTimeProf.c
BIN=main
COMPILER_FLAGS=-Wall -Wextra -g -std=c11
DEBUGGER=gdb

all:
	$(COMPILER) $(COMPILER_FLAGS) $(SRC) -o $(BIN)

run:
	$(BIN)

debug:
	$(DEBUGGER) $(BIN)

every: clean all run

every_debug: clean all debug

clean:
	del *.o *.exe TODO.txt