COMPILE = g++ -std=c++11
FLAGS = -Wall -Werror -pedantic
PATH = src/rshell.cc -o bin/rshell

all:
		rshell

rshell:
		mkdir bin
		$(COMPILE) $(FLAGS) $(PATH)

clean:
		rm -rf bin/
