#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>



//TODO this is WRONG :D
int64_t get_knight_mask(int pos) {
    int64_t mask = 0;
    int rs[8] = {2, 2, 1, -1 ,-2, -2, -1, 1};
    int cs[8] = {-1, 1, 2, 2, 1, -1, -2, -2};
    int i = 0;

    while (i < 8) {
        int r = rs[i];
        int c = cs[i];
        int from_pos = pos + r*8 + c;
        i++;
        // relevant for first/last 2 ranks 
        if (pos + 8*r < 0 || pos + 8*r > 63) {
            continue;
        }
        // extra check to not go to next row if on flank files
        if (pos + c < 0 || pos + c > 7) {
            continue;
        }
        mask |= (int64_t) 1 << from_pos;
    }
    return mask;
}

int64_t get_rook_mask(int pos) {
    int64_t mask = 0;
    int64_t vertical = 0x0101010101010101;
    int64_t horizontal = 0xff;
    int c_off = pos % 8;
    int r_off = pos / 8;
    mask |= (vertical << c_off) | (horizontal << r_off*8);
    mask &= ~((uint64_t) 1 << pos);
    return mask;
}
int64_t get_bishop_mask(int pos) {
    // rows and files to the left, left, down, and up
    int64_t mask = 0;
    int offsets[4] = {7, 9, -7, -9};
    int current = pos;
    int i = 0;
    while (i < 4) {
        // if current is on the edge of the board
        int bounds = 0;
        // top or botton
        if (i < 2) {
            bounds |= current > (63 - 8);
        } else {
            bounds |= current < 8;
        }
        // left or right
        bounds |= (current % 8) == (8 - (i % 2)) % 8;
        if (bounds) {
            current = pos;
            i++;
        } else {
            current += offsets[i];
            mask |= (int64_t) 1 << current;
            
        }
    }
    return mask;
}


int64_t get_mask(char piece, char* coord) {
    int64_t mask;
    int pos = (coord[1] - '1') * 8 + coord[0] - 'a';
    
    switch (piece) {
        case 'n':
            mask = get_knight_mask(pos);
            break;
        case 'r':
            mask = get_rook_mask(pos);
            break;
        case 'b':
            mask = get_bishop_mask(pos);
            break;
        //default:
            //mask = get_pawn_mask(pos);
    }
    return mask;
}