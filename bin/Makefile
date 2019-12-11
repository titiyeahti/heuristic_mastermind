CC = gcc -Wall -Wextra -ansi -Werror
SRC = ../src/

all : test.out

test.out : mastermind.o $(SRC)test.c
	$(CC) $^ -g -o $@

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@

clean:
	rm -rf *.out *.o
