#ifndef DATA_H
#define DATA_H

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

/* MACROS */

#define IsRQ(p) piece_rook_queen[(p)]
#define IsBQ(p) piece_bishop_queen[(p)]
#define IsKn(p) piece_knight[(p)]

/* GLOBALS */

#define BRD_SQ_NUM 120
#define MXGAMEMOVES 2048

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

/* GLOBALS */

extern const int piece_val[13];
extern const int piece_col[13];

extern const int piece_pawn[13];	
extern const int piece_knight[13];
extern const int piece_king[13];
extern const int piece_rook_queen[13];
extern const int piece_bishop_queen[13];
extern const int piece_slides[13];

extern const int N_dir[8];
extern const int R_dir[4];
extern const int B_dir[4];
extern const int K_dir[8];

extern int files_brd[BRD_SQ_NUM];
extern int ranks_brd[BRD_SQ_NUM];

#endif