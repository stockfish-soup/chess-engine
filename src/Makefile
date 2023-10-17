moves: moves.o main.o
	gcc -o moves moves.o main.o

moves.o: moves.c
	gcc -o moves.o -c moves.c -W -Wall -ansi -pedantic

main.o: main.c moves.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic