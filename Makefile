COMPILES = g++
IFLAGS = -Wall -Werror -ansi -pedantic
PATH = ./src/main.cpp
PATHK = ./bin/rshell

all:
		mkdir -p ./bin
		$(COMPILES) $(IFLAGS) $(PATH) -o $(PATHK)

rshell:	
		mkdir -p ./bin
		$(COMPILES) $(IFLAGS) $(PATH) -o $(PATHK)
clean:
		rm -rf ./bin
