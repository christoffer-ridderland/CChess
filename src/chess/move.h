#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H
typedef struct Square {
    int file;
    int rank;
} Square;

typedef struct Move {
    char* piece;
    int from;
    int to;
    int capture;
    int promotion;
    int en_passant;
    int castling;

} Move;

#endif