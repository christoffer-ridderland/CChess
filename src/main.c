#include <stdio.h>
#include <stdlib.h>
#include "misc/misc.h"
#include "chess/fen.h"
#include "chess/board.h"
#include "chess/move.h"
char* starting_board = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";



int main() {
    // Check that fen works
    Fen* my_fen = (Fen*) malloc((int) sizeof(Fen));
    zeroFen(my_fen);
    parseFen(starting_board, my_fen);
    printFen(my_fen);
    //free(my_fen);
    // Check that board works
    Board* my_board = (Board*) malloc((int) sizeof(Board));
    initPieces(my_fen->pieces, my_board);
    printBoard(*my_board);
    free(my_board);



    int64_t m = get_mask('b', "f1");
    printbf("bishop moved from:\n", m);
    printf("exiting succsessfully!\n");
    return 0;
}

 