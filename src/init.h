#ifndef INIT_H
#define INIT_H

/* FUNCTIONS */

extern void allInit();
extern void initBitMasks();
extern void initHashKeys();

/* GLOBALS */

extern U64 piece_keys[13][120];
extern U64 side_key;
extern U64 castle_keys[16];

#endif