#ifndef INIT_H
#define INIT_H

/* FUNCTIONS */

extern void allInit();
extern void initBitMasks();
extern void initHashKeys();
extern void initFilesRanksBrd();

/* GLOBALS */

extern U64 piece_keys[13][120];
extern U64 side_key;
extern U64 castle_keys[16];
extern int files_brd[BRD_SQ_NUM];
extern int ranks_brd[BRD_SQ_NUM];

#endif