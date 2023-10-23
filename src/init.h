#ifndef INIT_H
#define INIT_H

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

/* FUNCTIONS */

extern void allInit();
extern void initBitMasks();
extern void initHashKeys();

/* GLOBALS */

extern U64 piece_keys[13][120];
extern U64 side_key;
extern U64 castle_keys[16];



#endif