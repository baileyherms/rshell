ICOMPILES = g++
IFLAGS = -Wall -Werror -ansi -pedantic
PATHI = ./src/main.cpp
PATHB = ./src/ls.cpp
PATHK = ./bin/rshell
PATHJ = ./bin/ls

all: rshell ls

rshell:	
		mkdir -p ./bin
		$(ICOMPILES) $(IFLAGS) $(PATHB) -o $(PATHJ)

ls:	
		mkdir -p ./bin
		$(ICOMPILES) $(IFLAGS) $(PATHB) -o $(PATHK)

clean:
		rm -rf ./bin
