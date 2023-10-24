#ifndef ATTACKS_H
#define ATTACKS_H

/* MACROS */

#define isBQ(p) (piece_bishop_queen[(p)])
#define isRQ(p) (piece_rook_queen[(p)])
#define isN(p)  (piece_knight[(p)])
#define isK(p)  (piece_king[(p)])

/* FUNCTIONS */

extern U64 maskPawnAttacks(int sq, int side);

extern sqAttacked(const int sq, const int side, const Board *pos);

/* GLOBALS */

extern U64 pawn_attacks[2][64];

#endif