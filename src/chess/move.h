#ifndef MOVE_H
#define MOVE_H
typedef struct Move {
    char piece;
    int capture;
    char* destination;
    char disambig_f;
    char disambig_r;
    int check;
    int mate;
} Move;

int64_t get_knight_mask(int pos);
int64_t get_rook_mask(int pos);
int64_t get_bishop_mask(int pos);
int64_t get_knight_mask(int pos);
int64_t get_mask(char piece, char* coord);
int64_t from_where(Move* mv, Board* bo);

//void move(char* notation, Board* board);
void parse_move(char* move, Move* m);
void printmf(Move* mv);

#endif