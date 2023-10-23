gui: gui.o board.o hashkeys.o init.o
	gcc -Wno-format -o gui board.o gui.o hashkeys.o init.o -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

board.o: ../src/board.c
	gcc -o board.o -c ../src/board.c -W -Wall -ansi -pedantic

hashkeys.o: ../src/hashkeys.c
	gcc -o hashkeys.o -c ../src/hashkeys.c -W -Wall -ansi -pedantic

init.o: ../src/init.c
	gcc -o init.o -c ../src/init.c -W -Wall -ansi -pedantic

gui.o: gui.c ../src/board.h ../src/hashkeys.h ../src/init.h
	gcc -Wno-format -o gui.o -c gui.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
