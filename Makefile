ICOMPILES = g++
IFLAGS = -Wall -Werror -ansi -pedantic
PATHI = ./src/main.cpp
PATHB = ./src/ls.cpp
PATHC = ./src/rshell.cpp
PATHK = ./bin/rshell
PATHJ = ./bin/ls
PATHQ = ./bin/other

all: rshell ls other

rshell:	
		mkdir -p ./bin
		$(ICOMPILES) $(IFLAGS) $(PATHC) -o $(PATHK)

ls:	
		mkdir -p ./bin
		$(ICOMPILES) $(IFLAGS) $(PATHB) -o $(PATHJ)

other:
		mkdir -p ./bin
		$(ICOMPILES) $(IFLAGS) $(PATHI) -o $(PATHQ)

clean:
		rm -rf ./bin
