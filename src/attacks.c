#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "board.h"
#include "hashkeys.h"
#include "init.h"
#include "attacks.h"
#include "data.h"

U64 pawn_attacks[2][64];

U64 maskPawnAttacks(int sq, int side) {

	/* result attacks bitboard */
	U64 attacks = 0ULL;

	U64 bb = 0ULL;

	SETBIT(bb, sq);

	if (!side) {  /* white pawns */

	} else {  /* black pawns */

	}

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
