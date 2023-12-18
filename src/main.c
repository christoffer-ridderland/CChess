#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "chess/board.h"
#include "chess/move.h"
#include "misc/misc.h"
#include "chess/fen.h"

char* starting_board =  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
char* test_board =      "2r4N/3p4/1P1Q3K/B2P4/1pr1P2R/2n5/4kP1p/8 w KQkq - 0 1";

void main() {
    //struct FEN* fen = parseFEN(starting_board);

    Board* board = init_board(test_board); // board is allocated, so free it later
    printboard_info(*board); 
}