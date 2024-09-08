#ifndef BOARD_H
#define BOARD_H

#ifndef CHESS_COLOR
#define CHESS_COLOR
    typedef enum Color {
        WHITE,
        BLACK
    } Color;
#endif

// idk if this enum will be used
typedef enum Piece {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
} Piece;

typedef struct Board {
    int64_t white;
    int64_t black;

    int64_t pawns;
    int64_t rooks;
    int64_t knights;
    int64_t bishops;
    int64_t queens;
    int64_t kings;

    Color turn;
    int en_passant;
    
    char castling;
    int halfmove;
    int fullmove;
} Board;
int64_t all(Board* board);
int64_t empty(Board* board);

void setZero(Board* board);

void setPiece(int i, char piece, Color color, Board* board);

void initPieces(char* pieces, Board* board);

void printbf(char* affix, int64_t bitboard);

void printBoard(Board board);
#endif
