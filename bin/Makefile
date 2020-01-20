CC = gcc -Wall -Wextra -ansi
SRC = ../src/
LIBS = -lm

all : spread.out test.out

spread.out : mastermind.o metaheuristic.o neighbourg.o proba.o $(SRC)spread.c
	$(CC) $^ -g -o $@ $(LIBS)

test.out : mastermind.o metaheuristic.o neighbourg.o proba.o $(SRC)test.c
	$(CC) $^ -g -o $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
