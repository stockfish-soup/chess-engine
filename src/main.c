#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "board.h"
#include "init.h"
#include "hashkeys.h"

int main(int argc, char *argv[]){
	allInit();
	U64 bb = 845489562312;
	SETBIT(bb,2);
	printf("%d",countBits(bb));
	printBitBoard(bb);
	Board board[1];
	resetBoard(board);
	parseFen(START_FEN, board);
	printBoard(board);
	return EXIT_SUCCESS;
}