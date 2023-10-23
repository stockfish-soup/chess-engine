#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "hashkeys.h"

int sq120_to_sq64[BRD_SQ_NUM];
int sq64_to_sq120[64];

U64 set_mask[64];
U64 clear_mask[64];

char pce_char[] = ".PNBRQKpnbrqk";
char side_char[] = "wb-";
char rank_char[] = "12345678";
char file_char[] = "abcdefgh";

void initSq120To64() {

	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;

	for (index = 0; index < BRD_SQ_NUM; ++index) {
		sq120_to_sq64[index] = 65;
	}

	for (index = 0; index < 64; ++index) {
		sq64_to_sq120[index] = 120;
	}

	for (rank = RANK_1; rank <= RANK_8; ++rank) {
		for (file = FILE_A; file <= FILE_H; ++file) {
			sq = FR2SQ(file,rank);
			sq64_to_sq120[sq64] = sq;
			sq120_to_sq64[sq] = sq64;
			sq64++;
		}
	}

}

int parseFen(char *fen, Board *pos) {

	ASSERT(fen!=NULL);
	ASSERT(pos!=NULL);

	int  rank = RANK_8;
    int  file = FILE_A;
    int  piece = 0;
    int  count = 0;
    int  i = 0;
	int  sq64 = 0;
	int  sq120 = 0;

	resetBoard(pos);

	while ((rank >= RANK_1) && *fen) {
	    count = 1;
		switch (*fen) {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                piece = EMPTY;
                count = *fen - '0';
                break;

            case '/':
            case ' ':
                rank--;
                file = FILE_A;
                fen++;
                continue;

            default:
                printf("FEN error \n");
                return -1;
        }

		for (i = 0; i < count; i++) {
            sq64 = rank * 8 + file;
			sq120 = SQ120(sq64);
            if (piece != EMPTY) {
                pos->pieces[sq120] = piece;
            }
			file++;
        }
		fen++;
	}

	ASSERT(*fen == 'w' || *fen == 'b');

	pos->side = (*fen == 'w') ? WHITE : BLACK;
	fen += 2;

	for (i = 0; i < 4; i++) {
        if (*fen == ' ') {
            break;
        }
		switch(*fen) {
			case 'K': pos->castle_perm |= WKCA; break;
			case 'Q': pos->castle_perm |= WQCA; break;
			case 'k': pos->castle_perm |= BKCA; break;
			case 'q': pos->castle_perm |= BQCA; break;
			default:	     break;
        }
		fen++;
	}
	fen++;

	ASSERT(pos->castle_perm>=0 && pos->castle_perm <= 15);

	if (*fen != '-') {
		file = fen[0] - 'a';
		rank = fen[1] - '1';

		ASSERT(file>=FILE_A && file <= FILE_H);
		ASSERT(rank>=RANK_1 && rank <= RANK_8);

		pos->en_pas = FR2SQ(file,rank);
    }

	/* pos->pos_key = generatePosKey(pos); */

	/* UpdateListsMaterial(pos); */

	return 0;
}

void printBoard(const Board *pos) {

	int sq,file,rank,piece;

	printf("\nGame Board:\n\n");

	for(rank = RANK_8; rank >= RANK_1; rank--) {
		printf("%d  ",rank+1);
		for(file = FILE_A; file <= FILE_H; file++) {
			sq = FR2SQ(file,rank);
			piece = pos->pieces[sq];
			printf("%3c",pce_char[piece]);
		}
		printf("\n");
	}

	printf("\n   ");
	for(file = FILE_A; file <= FILE_H; file++) {
		printf("%3c",'a'+file);
	}
	printf("\n");
	printf("side:%c\n",side_char[pos->side]);
	printf("enPas:%d\n",pos->en_pas);
	printf("castle:%c%c%c%c\n",
			pos->castle_perm & WKCA ? 'K' : '-',
			pos->castle_perm & WQCA ? 'Q' : '-',
			pos->castle_perm & BKCA ? 'k' : '-',
			pos->castle_perm & BQCA ? 'q' : '-'
			);
	printf("PosKey:%llX\n",pos->pos_key);
}

void resetBoard(Board *pos) {

	int index;

	for (index = 0; index < BRD_SQ_NUM; ++index) {
		pos->pieces[index] = OFFBOARD;
	}

	for (index = 0; index < 64; ++index) {
		pos->pieces[SQ120(index)] = EMPTY;
	}

	for (index = 0; index < 13; ++index) {
		pos->pce_num[index] = 0;
	}

	pos->side = BOTH;
	pos->en_pas = NO_SQ;
	pos->fifty_moves = 0;

	pos->ply = 0;
	pos->his_ply = 0;

	pos->castle_perm = 0;

	pos->pos_key = 0ULL;
}

const int BitTable[64] = {
  63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
  51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
  26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
  58, 20, 37, 17, 36, 8
};

int popBit(U64 *bb) {
  U64 b = *bb ^ (*bb - 1);
  unsigned int fold = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
  *bb &= (*bb - 1);
  return BitTable[(fold * 0x783a9b23) >> 26];
}

int countBits(U64 y) {
	y -= ((y >> 1) & 0x5555555555555555ull);
	y = (y & 0x3333333333333333ull) + (y >> 2 & 0x3333333333333333ull);
	return ((y + (y >> 4)) & 0xf0f0f0f0f0f0f0full) * 0x101010101010101ull >> 56;
}

void printBitBoard(U64 bb) {

	U64 shiftMe = 1ULL;
	
	int rank = 0;
	int file = 0;
	int sq = 0;
	int sq64 = 0;
	
	printf("\n");
	for(rank = RANK_8; rank >= RANK_1; --rank) {
		for(file = FILE_A; file <= FILE_H; ++file) {
			sq = FR2SQ(file,rank);
			sq64 = sq120_to_sq64[sq]; 
			
			if((shiftMe << sq64) & bb) 
				printf("X");
			else 
				printf("_");
				
		}
		printf("\n");
	}  
    printf("\n\n");
}