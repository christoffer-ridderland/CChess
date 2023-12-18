#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "board.h"
#include "fen.h"

int64_t all(Board* board) {
    return board->white | board->black;
}
int64_t empty(Board* board) {
    return ~all(board);
}

void set_zero(Board* board) {
    board->white = 0;
    board->black = 0;

    board->pawns = 0;
    board->rooks = 0;
    board->knights = 0;
    board->bishops = 0;
    board->queens = 0;
    board->kings = 0;

}

void set_piece(int index, Color color, Board* c_board, int16_t* p_board ) {
    int64_t one = 1; // 1 in the 64th bit
    int64_t* board = (color == WHITE) ? &c_board->white : &c_board->black;
    *board |= one << index;
    *p_board |= one << index;
}
void init_pieces(char* pieces, Board* board) {
    set_zero(board);
    int64_t one = 1; // 1 in the 64th bit
    int row = 7;
    int col = 0;
    int ci = row * 8 + col;
    while(ci >= 0) {
        printf("%d\n", ci);
        Color color = BLACK;
        char c = pieces[ci];
        if (c == '0') {
            // do nothing
        }
        else if (isupper(c)) {
            color = WHITE;
            c += 32; // convert to lowercase
        }
        switch (c)
        {
        case 'p':
            set_piece(ci, color, board, &board->pawns);
            break;
        case 'r':
            set_piece(ci, color, board, &board->rooks);
            break;
        case 'n':
            set_piece(ci, color, board, &board->knights);
            break;
        case 'b':
            set_piece(ci, color, board, &board->bishops);
            break;
        case 'q':
            set_piece(ci, color, board, &board->queens);
            break;
        case 'k':
            set_piece(ci, color, board, &board->kings);
            break;
        default:
            printf("Invalid piece: %c\n", c);
            exit(1);
            break;
        }

        col++;
        if (col > 7) {
            col = 0;
            row--;
        }
        ci = row * 8 + col;
    }
}

Board* init_board(char* feNo) {
    Board* board = (Board*) malloc( ( int ) sizeof(Board));
    struct FEN* fen = parseFEN(feNo);
    init_pieces(fen->pieces, board);
    board->turn = fen->turn;
    board->en_passant = fen->en_passant;
    board->castling = fen->castling;
    board->halfmove = fen->halfmove;
    board->fullmove = fen->fullmove;

    free(fen);
    return board;
}

int64_t get_c_p(Color color, Board* board, int16_t p_board) {
    if (color == WHITE) {
        return board->white & p_board;
    }
    else {
        return board->black & p_board;
    }
}

void printbf(char* affix, int64_t binary) {
    printf("%s", affix);
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j <= 7; j++) {
            printf("%d" "", (int) (binary >> (i * 8 + j)) & 1);
        }
        printf("\n");
    }
    printf("\n\n");
}

void printboard_info(Board board) {
    printf("I am printing board info\n");
    printbf("all: \n", all(&board));
    printbf("empty: \n", empty(&board));
    printbf("white \n", board.white);
    printbf("black: \n", board.black);
    printbf("pawns: \n", board.pawns);
    printbf("rooks: \n", board.rooks);
    printbf("knights: \n", board.knights);
    printbf("bishops: \n", board.bishops);
    printbf("queens: \n", board.queens);
    printbf("kings: \n", board.kings);
    printf("turn: %d\n", board.turn);
    printf("en_passant: %d\n", board.en_passant);
    printf("castling: %d\n", board.castling);
    printf("halfmove: %d\n", board.halfmove);
    printf("fullmove: %d\n", board.fullmove);

    return 0;
}

