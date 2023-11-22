#ifndef INIT_H
#define INIT_H

/* FUNCTIONS */

extern void allInit();
extern void initBitMasks();
extern void initHashKeys();
extern void initFilesRanksBrd();
extern void initLeapersAttacks();
extern void initMagicNumbers();

/* GLOBALS */

extern U64 piece_keys[13][120];
extern U64 side_key;
extern U64 castle_keys[16];
extern int files_brd[BRD_SQ_NUM];
extern int ranks_brd[BRD_SQ_NUM];
extern unsigned int rook_magic_numbers[64];
extern unsigned int bishop_magic_numbers[64];
extern unsigned int state; /* for random number generation */

#endif