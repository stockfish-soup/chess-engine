#ifndef BOARD_H
#define BOARD_H

typedef unsigned long long int U64;

#define START_FEN  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef BRD_SQ_NUM
#define BRD_SQ_NUM 120
#endif


#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}

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

	U64 BB[13];

	int pieces[BRD_SQ_NUM];
	int pce_num[13];

	int side;
	int en_pas;
	int fifty_moves;
	int castle_perm;

	unsigned int ply;
	unsigned int his_ply;

	U64 pos_key;

} Board;

/* GAME MOVE */

/* MACROS */

#define FR2SQ(f,r) ( (21 + (f) ) + ( (r) * 10) ) 
#define SQ64(sq120) (sq120_to_sq64[(sq120)])
#define SQ120(sq64) (sq64_to_sq120[(sq64)])
#define POP(b) popBit(&b)

#define CNT(b) countBits(b)

#ifdef __GNUC__
/* Use GCC's built-in popcount for GCC compiler */
#define CNT(value) __builtin_popcountll(value)
#elif defined(_MSC_VER)
/* Use MSVC's popcnt64 for MSVC compiler */
#include <intrin.h>
#define CNT(value) __popcnt64(value)
#else
/* Use a custom implementation for other compilers */
int countBits(uint64_t value) {
	y -= ((y >> 1) & 0x5555555555555555ull);
	y = (y & 0x3333333333333333ull) + (y >> 2 & 0x3333333333333333ull);
	return ((y + (y >> 4)) & 0xf0f0f0f0f0f0f0full) * 0x101010101010101ull >> 56;
}
#define CNT(value) countBits(value)
#endif

#define CLRBIT(bb,sq) ((bb) &= clear_mask[(sq)])
#define SETBIT(bb,sq) ((bb) |= set_mask[(sq)])
#define RANK(sq) ((sq) >> 3) /* in 64, div 8 (sq120) */
#define FILE(sq) ((sq) & 7) /* in 64, modulo (sq120) */

/* GLOBALS */

extern int sq120_to_sq64[BRD_SQ_NUM];
extern int sq64_to_sq120[64];

extern U64 set_mask[64];
extern U64 clear_mask[64];

extern char pce_char[];
extern char side_char[];
extern char file_char[];
extern char rank_char[];

extern const U64 not_a_file;
extern const U64 not_h_file;

/* FUNCTIONS */

extern void initSq120To64();
extern void resetBoard(Board *pos);
extern void printBoard(const Board *pos);
extern int parseFen(char *fen, Board *pos); /* sets up board from fen */

/* BitBoards */

extern void printBB(const U64 bb); /* prints 'X' if 1 and '_' if 0 */
extern void setBB(Board *pos);
extern int popBit(U64 *bb); /* replaces the first 1 bit to 0 and returns the index */
extern U64 setOccupancy(int index, int bits_in_mask, U64 attack_mask);


#endif