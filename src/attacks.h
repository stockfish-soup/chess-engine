#ifndef ATTACKS_H
#define ATTACKS_H

/* MACROS */

#define isBQ(p) (piece_bishop_queen[(p)])
#define isRQ(p) (piece_rook_queen[(p)])
#define isN(p)  (piece_knight[(p)])
#define isK(p)  (piece_king[(p)])

/* FUNCTIONS */

extern U64 maskPawnAttacks(int sq, int side);
extern U64 maskBishopAttacks(int sq); /* without blocking pieces */
extern U64 maskRookAttacks(int sq); /* without blocking pieces */
extern U64 maskKingAttacks(int sq);
extern U64 maskKnightAttacks(int sq);

extern U64 bishopAttacks(int sq, U64 block); /* with blocking pieces */
extern U64 rookAttacks(int sq, U64 block); /* with blocking pieces */

extern int sqAttacked(const int sq, const int side, const Board *pos);

/* Random Numbers and Magic Numbers*/

extern unsigned int getRandomNumber(); /* to get a pseudo random number */
extern U64 getRandomU64(); 

extern U64 genMagicNumber();
extern U64 findMagicNumber(int sq, int relevant_bits, int bishop);

/* GLOBALS */

extern U64 pawn_attacks[2][64];
extern U64 knight_attacks[64];
extern U64 bishop_attacks[64];
extern U64 rook_attacks[64];
extern U64 king_attacks[64];
extern const int bishop_relevant_bits[64];
extern const int bishop_relevant_bits[64];

#endif