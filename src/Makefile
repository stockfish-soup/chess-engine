init: board.o init.o hashkeys.o 
	gcc -o engine board.o init.o hashkeys.o

board.o: board.c
	gcc -o board.o -c board.c -W -Wall -ansi -pedantic

init.o: init.c board.h init.h hashkeys.h
	gcc -o init.o -c init.c -W -Wall -ansi -pedantic

hashkeys.o: hashkeys.c
	gcc -o hashkeys.o -c hashkeys.c -W -Wall -ansi -pedantic

