engine: main.o board.o init.o hashkeys.o 
	gcc -o engine main.o board.o init.o hashkeys.o

init.o: init.c
	gcc -o init.o -c init.c -W -Wall -ansi -pedantic

board.o: board.c
	gcc -o board.o -c board.c -W -Wall -ansi -pedantic

main.o: main.c board.h init.h hashkeys.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

hashkeys.o: hashkeys.c
	gcc -o hashkeys.o -c hashkeys.c -W -Wall -ansi -pedantic

