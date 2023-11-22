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
#include "moves.h"


void printMove(unsigned long move) {

    unsigned int from, to, captured, promoted;

    from = FROMSQ(move);
    to = TOSQ(move);
    captured = CAPTURED(move);
    promoted = PROMOTED(move);

    printf("From : %d\n",from);
    printf("To : %d\n",to);
    printf("Promoted Piece : %d\n",promoted);
    printf("Captured Piece : %d\n",captured);

    static char MvStr[6];

	int ff = files_brd[SQ120(FROMSQ(move))];
	int rf = ranks_brd[SQ120(FROMSQ(move))];
	int ft = files_brd[SQ120(TOSQ(move))];
	int rt = ranks_brd[SQ120(TOSQ(move))];

	if(promoted) {
		char pchar = 'q';
		if(IsKn(promoted)) {
			pchar = 'n';
		} else if(IsRQ(promoted) && !IsBQ(promoted))  {
			pchar = 'r';
		} else if(!IsRQ(promoted) && IsBQ(promoted))  {
			pchar = 'b';
		}
		sprintf(MvStr, "%c%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt), pchar);
	} else {
		sprintf(MvStr, "%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt));
	}

    printf(MvStr);

}