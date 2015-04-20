COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
PATH = src/hw0.cpp
PATHK = ./bin/rshell

all: rshell

rshell:	
		mkdir -p ./bin
		$(COMPILE) $(FLAGS) $(PATH) -o $(PATHK)
clean:
		rm -rf ./bin
