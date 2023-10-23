#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "board.h"
#include "init.h"
#include "hashkeys.h"

#define RAND_64 	((U64)rand() | \
					(U64)rand() << 15 | \
					(U64)rand() << 30 | \
					(U64)rand() << 45 | \
					((U64)rand() & 0xf) << 60 )

U64 piece_keys[13][120];
U64 side_key;
U64 castle_keys[16];

void initBitMasks() {

	int index = 0;

	for(index = 0; index < 64; index++) {
		set_mask[index] = 0ULL;
		clear_mask[index] = 0ULL;
	}

	for(index = 0; index < 64; index++) {
		set_mask[index] = (1ULL << index);
		clear_mask[index] = ~set_mask[index];
	}
}

void initHashKeys(){

	int index = 0;
	int index2 = 0;

	for (index = 0; index < 13; ++index) {
		for (index2 = 0; index2 < 120; ++index2) {
			piece_keys[index][index2] = RAND_64;
		}
	}

	side_key = RAND_64;

	for (index = 0; index < 16; ++index) {
		castle_keys[index] = RAND_64;
	}
}

void allInit() {
	printf("Hello World\n");
	initSq120To64();
	initBitMasks();
	initHashKeys();
}

int main(int argc, char *argv[]){
	allInit();
	ASSERT(0);
	U64 bb = 845489562312;
	SETBIT(bb,2);
	printf("%d",countBits(bb));
	printBitBoard(bb);
	return EXIT_SUCCESS;
}