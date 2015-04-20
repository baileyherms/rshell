COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic
all:
	mkdir -p ./bin
	$(COMPILE) $(FLAGS) ./src/main.cpp -o ./bin/rshell

rshell:
	mkdir -p ./bin
	$(COMPILE) $(FLAGS) ./src/main.cpp -o ./bin/rshell
clean:
	rm -rf ./bin
