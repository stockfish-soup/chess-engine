#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "board.h"
#include "hashkeys.h"
#include "init.h"
#include "attacks.h"
#include "data.h"
#include "moves.h"

/* bishop relevant occupancy bit count for every square on board */
const int bishop_relevant_bits[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

/* rook relevant occupancy bit count for every square on board */
const int rook_relevant_bits[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12
};

U64 maskPawnAttacks(int sq, int side) { /* sq64 */

	/* result attacks bitboard */
	U64 attacks = 0ULL;

	U64 bb = 0ULL;

	SETBIT(bb, sq);

	if (!side) {  /* white pawns */

		if ((bb >> 7) & not_a_file) attacks |= (bb >> 7);
		if ((bb >> 9) & not_h_file) attacks |= (bb >> 9);

	} else {  /* black pawns */

		if ((bb << 7) & not_h_file) attacks |= (bb << 7);
		if ((bb << 9) & not_a_file) attacks |= (bb << 9);

	}
	
	return attacks;

}

U64 maskKnightAttacks(int sq) {

	U64 attacks = 0ULL;
	int i;
	int attack;

	for (i = 0; i < 8; i++) {

		attack = SQ64(SQ120(sq) + N_dir[i]);

		if (attack != 65) {
			SETBIT(attacks, attack);
		}
	}

	return attacks;

}

U64 maskKingAttacks(int sq) {

	U64 attacks = 0ULL;
	int i;
	int attack;

	for (i = 0; i < 8; i++) {

		attack = SQ64(SQ120(sq) + K_dir[i]);

		if (attack != 65) {
			SETBIT(attacks, attack);
		}
	}

	return attacks;

}

U64 bishopAttacks(int sq, U64 block) {

	U64 attacks = 0ULL;

	int r, f;

	int tr = sq / 8;
	int tf = sq % 8;

	for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f) & block)) break;
	}

	for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f) & block)) break;
	}

	for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f) & block)) break;
	}

	for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f) & block)) break;
	}

	return attacks;

}

U64 rookAttacks(int sq, U64 block) {

	U64 attacks = 0ULL;

	int r, f;

	int tr = sq / 8;
	int tf = sq % 8;

	for (r = tr + 1, f = tf; r <= 6; r++) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f) & block)) break;
	}

	for (r = tr - 1, f = tf; r >= 1; r--) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f) & block)) break;
	}

	for (f = tf + 1, r = tr; f <= 6; f++) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f) & block)) break;
	}

	for (f = tf - 1, r = tr; f >= 1; f--) {
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f) & block)) break;
	}

	return attacks;

}

U64 maskBishopAttacks(int sq) {

	U64 attacks = 0ULL;

	int r, f;

	int tr = sq / 8;
	int tf = sq % 8;

	for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));
	for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));

	return attacks;

}

U64 maskRookAttacks(int sq) {

	U64 attacks = 0ULL;

	int r, f;

	int tr = sq / 8;
	int tf = sq % 8;

	for (r = tr + 1, f = tf; r <= 6; r++) attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf; r >= 1; r--) attacks |= (1ULL << (r * 8 + f));
	for (f = tf + 1, r = tr; f <= 6; f++) attacks |= (1ULL << (r * 8 + f));
	for (f = tf - 1, r = tr; f >= 1; f--) attacks |= (1ULL << (r * 8 + f));

	return attacks;

}


int sqAttacked(const int sq, const int side, const Board *pos) {   /* sq in 120 */

	int pce,index,t_sq,dir;
	
	/* pawns */
	if(side == WHITE) {
		if(pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP) {
			return TRUE;
		}
	} else {
		if(pos->pieces[sq+11] == bP || pos->pieces[sq+9] == bP) {
			return TRUE;
		}	
	}
	
	/* knights */
	for(index = 0; index < 8; ++index) {		
		pce = pos->pieces[sq + N_dir[index]];
		if(pce != OFFBOARD && isN(pce) && piece_col[pce]==side) {
			return TRUE;
		}
	}
	
	/* rooks, queens */
	for(index = 0; index < 4; ++index) {		
		dir = R_dir[index];
		t_sq = sq + dir;
		pce = pos->pieces[t_sq];
		while(pce != OFFBOARD) {
			if(pce != EMPTY) {
				if(isRQ(pce) && piece_col[pce] == side) {
					return TRUE;
				}
				break;
			}
			t_sq += dir;
			pce = pos->pieces[t_sq];
		}
	}
	
	/* bishops, queens */
	for(index = 0; index < 4; ++index) {		
		dir = B_dir[index];
		t_sq = sq + dir;
		pce = pos->pieces[t_sq];
		while(pce != OFFBOARD) {
			if(pce != EMPTY) {
				if(isBQ(pce) && piece_col[pce] == side) {
					return TRUE;
				}
				break;
			}
			t_sq += dir;
			pce = pos->pieces[t_sq];
		}
	}
	
	/* kings */
	for(index = 0; index < 8; ++index) {		
		pce = pos->pieces[sq + K_dir[index]];
		if(pce != OFFBOARD && isK(pce) && piece_col[pce]==side) {
			return TRUE;
		}
	}
	
	return FALSE;

}

unsigned int getRandomNumber() {

	unsigned int number = state;

	number ^= number << 12;
	number ^= number >> 17;
	number ^= number << 5;

	state = number;

	return number;

}

U64 getRandomU64() {

	int n1, n2, n3, n4;

	n1 = getRandomNumber() & 0xFFFF;
	n2 = getRandomNumber() & 0xFFFF;
	n3 = getRandomNumber() & 0xFFFF;
	n4 = getRandomNumber() & 0xFFFF;

	return (U64) (((U64)n1) | ((U64)n2 << 16) | ((U64)n3 << 32) | ((U64)n4 << 48));

}

U64 genMagicNumber() {

	return getRandomU64() & getRandomU64() & getRandomU64();

}

U64 findMagicNumber(int sq, int relevant_bits, int bishop) { /* 1 if bishop else 0 */

	U64 occupancies[4096];
	U64 attacks[4096];
	U64 used_attacks[4096];
	U64 attack_mask = bishop ? maskBishopAttacks(sq) : maskRookAttacks(sq);
	U64 magic_number = genMagicNumber();
	int occupancy_indicies = 1 << relevant_bits;
	int index, random_count, fail, magic_index;

	for (index = 0; index < occupancy_indicies; index++) {

		occupancies[index] = setOccupancy(index, relevant_bits, attack_mask);
		attacks[index] = bishop ? bishopAttacks(sq, occupancies[index]) : rookAttacks(sq, occupancies[index]);

	}

	/* test magic number loop */

	for (random_count = 0; random_count < 100000000; random_count++) {

		magic_number = genMagicNumber(); /* gen magic number */

		/* skip inappropriate magic numbers */

		if (CNT((attack_mask * magic_number) & 0xFF00000000000000) < 6) continue;

		memset(used_attacks, 0ULL, sizeof(used_attacks)); /* init used attacks */

		for (index = 0, fail = 0; !fail && index < occupancy_indicies; index++) {

			magic_index = (int)(occupancies[index] * magic_number) >> (64 - relevant_bits);
			if (used_attacks[index] == 0ULL) used_attacks[index]; /* if magic index works init used attacks */
			else if (used_attacks[index] != attacks[index]) fail = 1; /* if it doesn't work set fail to 1 */

		}

		if (!fail) return magic_number;

	}

	printf("magic number fails\n");
	return 0ULL;

}