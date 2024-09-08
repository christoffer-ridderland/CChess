#ifndef MOVE_H
#define MOVE_H


int64_t get_knight_mask(int pos);
int64_t get_rook_mask(int pos);
int64_t get_bishop_mask(int pos);
int64_t get_mask(char piece, char* coord);
#endif