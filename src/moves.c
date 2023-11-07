#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "board.h"
#include "hashkeys.h"
#include "init.h"
#include "attacks.h"
#include "data.h"
#include "attacks.h"


void printMove(unsigned long move) {

    unsigned int from, to, piece_captured, piece_promoted;

    from = FROMSQ(move);
    to = TOSQ(move);
    piece_captured = CAPTURED(move);
    piece_promoted = PROMOTED(move);

    printf("From : %d\n",from);
    printf("To : %d\n",to);
    printf("Promoted Piece : %d\n",piece_promoted);
    printf("Captured Piece : %d\n",piece_captured);

}