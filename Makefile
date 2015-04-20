COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
all:
	rshell

rshell:
	mkdir -p ./bin
	$(COMPILE) $(FLAGS) ./src/hw0.cpp -o ./bin/rshell
clean:
	rm -rf ./bin
