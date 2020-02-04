CC = gcc -Wall -Wextra -ansi
SRC = ../src/
LIBS = -lm

all : test.out

test.out : mastermind.o  $(SRC)test.c
	$(CC) $^ -g -o $@ $(LIBS)

%.o : $(SRC)%.c $(SRC)%.h
	$(CC) -c -g $< -o $@ $(LIBS)

clean:
	rm -rf *.out *.o
