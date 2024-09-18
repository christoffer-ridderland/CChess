#include <stdio.h>
#include <stdlib.h>
#include "misc/misc.h"
#include "chess/fen.h"
#include "chess/board.h"
#include "chess/move.h"
char* starting_board = "rnbqkbnr/pppppppp/8/8/8/r7/PPPPPPPP/RNBQKBNR b KQkq - 0 1";



int main() {
    // Check that fen works
    

    Fen* my_fen = parseFen(starting_board);
    printf("Fen: %s\n", my_fen->pieces);
    printFen(my_fen);
    //free(my_fen);
    // Check that board works
    Board* my_board = (Board*) malloc((int) sizeof(Board));
    initPieces(my_fen->pieces, my_board);
    printBoard(*my_board);



    int64_t m = get_mask('B', "d3");
    printbf("bishop move:\n", m);
    //printf("exiting succsessfully!\n");
    Move* mv = (Move*) malloc((int) sizeof(Move));
    parse_move("Bd3", mv);
    printmf(mv);
    m = from_where(mv, my_board);
    printbf("It came from:\n", m);
    //free(my_board);
    return 0;
}

 