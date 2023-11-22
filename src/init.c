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

U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 bishop_attacks[64];
U64 rook_attacks[64];
U64 king_attacks[64];

unsigned int rook_magic_numbers[64];
unsigned int bishop_magic_numbers[64];

unsigned int state = 8548319552;

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

void initLeaperAttacks() {

	int sq; /* sq64 */

	for (sq = 0; sq < 64; sq++) {
		
		pawn_attacks[WHITE][sq] = maskPawnAttacks(sq, WHITE);
		pawn_attacks[BLACK][sq] = maskPawnAttacks(sq, BLACK);

		knight_attacks[sq] = maskKnightAttacks(sq);
		king_attacks[sq] = maskKingAttacks(sq);

	}

}

void initMagicNumbers() {

	int sq;
	
	for (sq = 0; sq < 64; sq++) printf("0x%lluxULL\n", findMagicNumber(sq, bishop_relevant_bits[sq], 1)); /* init magic numbers for bishop */
	for (sq = 0; sq < 64; sq++) printf("0x%lluxULL\n", findMagicNumber(sq, bishop_relevant_bits[sq], 0)); /* init magic numbers for rook */


}

void allInit() {
	printf("Hello World\n");
	initSq120To64();
	initBitMasks();
	initHashKeys();
	initFilesRanksBrd();
	initLeaperAttacks();
	initMagicNumbers();
}