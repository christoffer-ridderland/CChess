#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "board.h"
#include "../misc/misc.h"
int64_t all(Board* board) {
    return board->white | board->black;
}

// might not need this
int64_t empty(Board* board) {
    return ~all(board);
}

void setZero(Board* board) {
    board->white = 0;
    board->black = 0;

    board->pawns = 0;
    board->rooks = 0;
    board->knights = 0;
    board->bishops = 0;
    board->queens = 0;
    board->kings = 0;
}

void setPiece(int i, char piece, Color color, Board* board) {
    int64_t* c_board;
    if (color == WHITE)
        c_board = &board->white;
    else
        c_board = &board->black;
    int64_t* p_board;
    switch (piece){
    case '0':
        //*c_board &= (int64_t) 0 << i;
        return;
    case 'p':
        p_board = &board->pawns;
        //printf("%d ", i);
        break;
    case 'r':
        p_board = &board->rooks;
        break;
    case 'n':
        p_board = &board->knights;
        break;
    case 'b':
        p_board = &board->bishops;
        break;
    case 'q':
        p_board = &board->queens;
        break;
    case 'k':
        p_board = &board->kings;
        break;
    }
    *c_board |= (int64_t) 1 << i;
    *p_board |= (int64_t) 1 << i;
}

void initPieces(char* pieces, Board* board) {
    setZero(board);
    int row = 7;
    int col = 0;
    int i = row * 8 + col;
    
    while (i >= 0) {
        char c = pieces[i];
        Color color = BLACK;
        if (c == '0') {
            // nothing
        } else if (isupper(c)) {
            color = WHITE;
            c += 32;
        }
        setPiece(i, c, color, board);
        //printbf("so far:", board->black);
        col++;
        if (col > 7) {
            col = 0;
            row--;
        }
        i = row * 8 + col;
    }
}

void printbf(char* affix, int64_t bitboard) {
    printf("%s", affix);
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j <= 7; j++) {
            printf("%d" "", (int) (bitboard >> (i * 8 + j)) & 1);
        }
        printf("\n");
    }
    printf("\n\n");
}

void printBoard(Board board) {
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

}
