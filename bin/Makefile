CC = gcc -Wall -Wextra -ansi
SRC = ../src/
LIBS = -lm

all : test.out rls.out ea.out

ea.out : mastermind.o metaheuristic.o $(SRC)ea.c
	$(CC) $^ -g -o $@ $(LIBS)

rls.out : mastermind.o metaheuristic.o $(SRC)rls.c
	$(CC) $^ -g -o $@ $(LIBS)

test.out : mastermind.o $(SRC)test.c
	$(CC) $^ -g -o $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
