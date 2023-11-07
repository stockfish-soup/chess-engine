engine: main.o board.o init.o hashkeys.o attacks.o data.o moves.o
	gcc -o engine main.o board.o init.o hashkeys.o attacks.o data.o moves.o

init.o: init.c
	gcc -o init.o -c init.c -W -Wall -ansi -pedantic

board.o: board.c
	gcc -o board.o -c board.c -W -Wall -ansi -pedantic

main.o: main.c board.h init.h hashkeys.h attacks.h data.h
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

hashkeys.o: hashkeys.c
	gcc -o hashkeys.o -c hashkeys.c -W -Wall -ansi -pedantic

attacks.o: attacks.c
	gcc -o attacks.o -c attacks.c -W -Wall -ansi -pedantic

data.o: data.c
	gcc -o data.o -c data.c -W -Wall -ansi -pedantic

moves.o: moves.c
	gcc -o moves.o -c moves.c -W -Wall -ansi -pedantic
