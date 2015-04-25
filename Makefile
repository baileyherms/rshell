ICOMPILES = g++
IFLAGS = -Wall -Werror -ansi -pedantic
PATHI = ./src/main.cpp
PATHK = ./bin/rshell

all: rshell

rshell:	
		mkdir -p ./bin
		$(ICOMPILES) $(IFLAGS) $(PATHI) -o $(PATHK)
clean:
		rm -rf ./bin
