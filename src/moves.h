#ifndef MOVES_H
#define MOVES_H

/* MACROS */

/* GAME MOVE type  

0000 0000 0000 0011 1111 -> from
0000 0000 1111 1100 0000 -> to
0000 1111 0000 0000 0000 -> captured
1111 0000 0000 0000 0000 -> promoted piece

*/

#define FROMSQ(m) ((m) & 0x3F)
#define TOSQ(m) (((m) >> 6) & 0x3F)
#define CAPTURED(m) (((m) >> 12) & 0xF)
#define PROMOTED(m) (((m) >> 16) & 0xF)

/* FUNCTIONS */

extern void printMove(unsigned long move);

#endif