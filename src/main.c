#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "board.h"
#include "init.h"
#include "hashkeys.h"
#include "data.h"
#include "attacks.h"
#include "moves.h"

int main(int argc, char *argv[]){
	allInit();
	U64 bb = 0;
	SETBIT(bb,2);
	printf("%d",countBits(bb));
	printBB(bb);
	Board board[1];
	resetBoard(board);
	parseFen(START_FEN, board);
	printBoard(board);
	printf("%d", sqAttacked(B5, WHITE, board));
	return EXIT_SUCCESS;
}