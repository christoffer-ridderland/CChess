#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H
#include <stdint.h>




typedef enum Piece {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
} Piece;

#ifndef CHESS_COLOR
#define CHESS_COLOR
    typedef enum Color {
        WHITE,
        BLACK
    } Color;
#endif


typedef struct Board {
    int64_t white;
    int64_t black;
    
    int64_t pawns;
    int64_t rooks;
    int64_t knights;
    int64_t bishops;
    int64_t queens;
    int64_t kings;

    Color turn;  // white or black
    int en_passant; // target square of en passant, if any, else -1. after move e4, en_passant would be 20
    char castling; // KQkq would be 0b1111, Qk would be 0b0110, etc.
    int halfmove; // number of halfmoves since last capture or pawn advance, used for 50 move rule
    int fullmove; // starts at 1, incremented after black moves
} Board;



Board* init_board(char* feNo);
void printboard_info(Board board);

#endif