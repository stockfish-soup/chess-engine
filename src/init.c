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

#define RAND_64 	((U64)rand() | \
					(U64)rand() << 15 | \
					(U64)rand() << 30 | \
					(U64)rand() << 45 | \
					((U64)rand() & 0xf) << 60 )

U64 piece_keys[13][120];
U64 side_key;
U64 castle_keys[16];
int files_brd[BRD_SQ_NUM];
int ranks_brd[BRD_SQ_NUM];

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

void initFilesRanksBrd() {

	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;

	for(index = 0; index < BRD_SQ_NUM; ++index) {
		files_brd[index] = OFFBOARD;
		ranks_brd[index] = OFFBOARD;
	}

	for(rank = RANK_1; rank <= RANK_8; ++rank) {
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = FR2SQ(file,rank);
			files_brd[sq] = file;
			ranks_brd[sq] = rank;
		}
	}
}

void allInit() {
	printf("Hello World\n");
	initSq120To64();
	initBitMasks();
	initHashKeys();
	initFilesRanksBrd();
}