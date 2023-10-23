#ifndef BOARD_H
#define BOARD_H

typedef unsigned long long int U64;

#define BRD_SQ_NUM 120
#define MXGAMEMOVES 2048

#define START_FEN  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}


/* ENUM */

enum {WHITE,BLACK,BOTH};
enum {EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK};
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE};
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE};
enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8}; 

/*

	0001 : White can castle Kingside
	0011 : White can castle Kingside and Queenside 
	etc ...

*/


/* STRUCTS */


typedef struct {

	unsigned int move;
	int side;
	int en_pas;
	int fifty_moves;
	int castle_perm;

	U64 pos_key;


} Undo;

typedef struct {

	/*
	U64 wP, wN, wB, wR, wQ, bP, bN, bB, bR, bQ;
	int wK, bK;
	*/

	int pieces[BRD_SQ_NUM];
	int pce_num[13];
	U64 pawns[3];

	int side;
	int en_pas;
	int fifty_moves;
	int castle_perm;

	unsigned int ply;
	unsigned int his_ply;

	U64 pos_key;

} Board;

/* MACROS */

#define FR2SQ(f,r) ( (21 + (f) ) + ( (r) * 10) ) 
#define SQ64(sq120) (sq120_to_sq64[(sq120)])
#define SQ120(sq64) (sq64_to_sq120[(sq64)])
#define POP(b) popBit(b)
#define CNT(b) countBits(b)
#define CLRBIT(bb,sq) ((bb) &= clear_mask[(sq)])
#define SETBIT(bb,sq) ((bb) |= set_mask[(sq)])

/* GLOBALS */

extern int sq120_to_sq64[BRD_SQ_NUM];
extern int sq64_to_sq120[64];

extern U64 set_mask[64];
extern U64 clear_mask[64];

extern char pce_char[];
extern char side_char[];
extern char file_char[];
extern char rank_char[];

/* FUNCTIONS */

extern void initSq120To64();
extern void resetBoard(Board *pos);
extern void printBoard(const Board *pos);
extern int parseFen(char *fen, Board *pos); /* sets up board from fen */

/* BitBoards */

extern void printBitBoard(U64 bb); /* prints 'X' if 1 and  '_' if 0 */
extern int popBit(U64 *bb); /* replaces the first 1 bit to 0 */
extern int countBits(U64 b); /* counts total number of 1 bits */

#endif