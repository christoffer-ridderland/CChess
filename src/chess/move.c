#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "move.h"
#include "board.h"

#define PAWN_MOVE 0
#define PAWN_CAPTURE 1
#define PIECE_MOVE 2
#define PIECE_CAPTURE 3
#define CASTLE 4
#define PROMOTION 5
#define PROMOTION_CAPTURE 6
#define EN_PASSANT 7
#define SINGLE_DISAMBIGUATION 8
#define DOUBLE_DISAMBIGUATION 9

int parsePawnMove(const char* notation, Square* from, Square* to) {
    if (strlen(notation) == 2 &&
        notation[0] >= 'a' && notation[0] <= 'h' &&
        notation[1] >= '1' && notation[1] <= '8') {
        from->file = notation[0];
        from->rank = notation[1] - '0';
        
        // Determine the target square based on the rank
        if (from->rank >= 2 && from->rank <= 7) {
            to->file = notation[0];
            if (from->rank == 2) {
                to->rank = 4;
            } else if (from->rank == 7) {
                to->rank = 5;
            } else {
                to->rank = from->rank + 1;
            }
            return 1; // Valid pawn move
        }
    }
    
    return 0; // Invalid format
}



// [piece][position]
// [piece]x[position]
// [piece](file)[position]
// [piece](file)x[position]
// [piece](rank)[position]
// [piece](rank)x[position]
// [piece](file)(rank)[position]
// [piece](file)(rank)x[position]
// O-O
// O-O-O
// [position]=[piece]
Move parse_move(char* move_str) {
    static Move move;
    int p_len = 0;
    char piece[3] = 0; // Disambiguation
    int len = strlen(move_str);
    int iter = 0;
    for (int i = 0; i < len; i++) {
        if iter =
    }
    return move;
}
    


int move_is_legal(Board* board, Move move) {

}
