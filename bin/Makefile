CC = gcc -Wall -Wextra -ansi
SRC = ../src/

all : test.out

test.out : mastermind.o metaheuristic.o $(SRC)test.c
	$(CC) $^ -g -o $@

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@

clean:
	rm -rf *.out *.o
