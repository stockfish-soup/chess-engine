#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "board.h"
#include "hashkeys.h"
#include "init.h"

/*

U64 generatePosKey(const Board *pos) {

	int sq = 0;
	U64 final_key = 0;
	int piece = EMPTY;
	
	// pieces
	for(sq = 0; sq < BRD_SQ_NUM; ++sq) {
		piece = pos->pieces[sq];
		if(piece!=NO_SQ && piece!=EMPTY && piece != OFFBOARD) {
			ASSERT(piece>=wP && piece<=bK);
			final_key ^= piece_keys[piece][sq];
		}		
	}
	
	if(pos->side == WHITE) {
		final_key ^= SideKey;
	}
		
	if(pos->en_pas != NO_SQ) {
		ASSERT(pos->en_pas>=0 && pos->en_pas<BRD_SQ_NUM);
		ASSERT(SqOnBoard(pos->en_pas));
		ASSERT(RanksBrd[pos->en_pas] == RANK_3 || RanksBrd[pos->en_pas] == RANK_6);
		final_key ^= piece_keys[EMPTY][pos->en_pas];
	}
	
	ASSERT(pos->castle_perm>=0 && pos->castle_perm<=15);
	
	final_key ^= castle_keys[pos->castle_perm];
	
	return final_key;
}

*/