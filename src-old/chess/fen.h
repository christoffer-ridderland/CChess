#ifndef FEN_H
#define FEN_H

#ifndef CHESS_COLOR
#define CHESS_COLOR
    typedef enum Color {
        WHITE,
        BLACK
    } Color;
#endif

struct FEN {
    char* pieces;
    Color turn; // white or black
    char castling; // KQkq would be 0b1111, Qk would be 0b0110, etc.
    int en_passant; // target square of en passant, if any, else "-" the move e4 would be "e3"
    int halfmove; // number of halfmoves since last capture or pawn advance, used for 50 move rule
    int fullmove; // starts at 1, incremented after black moves
} FEN;

struct FEN* parseFEN(char* fen);
void printfen(struct FEN* fen);

#endif