#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include "board.h"
#include "move.h"


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
        if (from_pos < 0 || from_pos > 63) {
            continue;
        }
        // extra check to not go to next/pervious rank if on flank files
        if ((pos % 8) + c < 0 || (pos % 8) + c > 7) {
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
    int offsets[4] = {7, 9, -9, -7};
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
        // left or right without if statement
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

int64_t get_king_mask(int pos) {
    int64_t mask = 0;
    int offsets[9] = {7,8,9, -1,0,1, -9,-8,-7};
    int i = 0;
    while (i < 9) {
        int bounds = 0;
        if (i < 3) {
            bounds |= pos > (63 - 8); 
        } else if (i > 5) {
            bounds |= pos < 8;
        }

        if (i % 3 == 0) {
            bounds |= pos % 8 == 0;
        } else if (i % 3 == 2) {
            bounds |= pos % 8 == 7;
        }
        if (!bounds) {
            mask |= (uint64_t) 1 << (pos + offsets[i]);
        }
        i++;
    }
    mask &= ~((int64_t) 1 << pos);
    return mask;
}

int64_t get_x_pawn_mask(int pos) {
    int64_t mask = get_king_mask(pos) & ~get_rook_mask(pos);
    return mask;
}

int64_t get_mask(char piece, char* coord) {
    int64_t mask;
    int pos = (coord[1] - '1') * 8 + coord[0] - 'a';
    
    switch (piece) {
        case 'N':
            mask = get_knight_mask(pos);
            break;
        case 'R':
            mask = get_rook_mask(pos);
            break;
        case 'B':
            mask = get_bishop_mask(pos);
            break;
        case 'Q':
            mask = get_bishop_mask(pos) | get_rook_mask(pos);
            break;
        case 'K':
            mask = get_king_mask(pos);
            break;
        case 'P':
            mask = get_x_pawn_mask(pos);
            break;
        //default:
            //mask = get_pawn_mask(pos);
    }
    return mask;
}
void parse_move(char* move, Move* m) {
    // Declare variables to hold parsed move components
    m->piece = 'P';  // Default to Pawn if no piece specified
    char destination[3] = {0};


    // Regex pattern that accounts for double disambiguation
    const char* pattern = "^([KQRBN])?([a-h])?([1-8])?(x)?([a-h][1-8])(\\+|\\#)?$";
    
    // Compile regex
    regex_t regex;
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        printf("Could not compile regex\n");
        return;
    }

    // Array to store match positions
    regmatch_t matches[7];
    
    // Execute regex on the move
    if (!regexec(&regex, move, 7, matches, 0)) {
        // Extract piece (if present)
        if (matches[1].rm_so != -1) {
            m->piece = move[matches[1].rm_so];
        }

        // Extract disambiguation (file if present)
        if (matches[2].rm_so != -1) {
            m->disambig_f = move[matches[2].rm_so];
        }

        // Extract disambiguation (rank if present)
        if (matches[3].rm_so != -1) {
            m->disambig_r = move[matches[3].rm_so];
        }

        // Check if it's a capture
        if (matches[4].rm_so != -1) {
            m->capture = 1;  // Set capture to true
        }

        // Extract destination square
        if (matches[5].rm_so != -1) {
            strncpy(destination, move + matches[5].rm_so, 2);  // Copy the destination (e.g., "e4")
            m->destination = destination;
        }

        // Check for check (+) or mate (#)
        if (matches[6].rm_so != -1) {
            if (move[matches[6].rm_so] == '+') {
                m->check = 1;
            } else if (move[matches[6].rm_so] == '#') {
                m->mate = 1;
            }
        }

    } else {
        printf("Invalid move format\n");
    }

    // Free the compiled regex
    regfree(&regex);
}

void printmf(Move* mv) {
    printf("\npiece :%c", mv->piece);
    printf("\ncapture :%d", mv->capture);
    printf("\ndestination :%s", mv->destination);
    printf("\ndisambig_f :%c", mv->disambig_f);
    printf("\ndisambig_r :%c", mv->disambig_r);
    printf("\ncheck :%d", mv->check);
    printf("\nmate :%d", mv->mate);
}
void move_piece(Move* mv, Board* bo) {
    
}
int64_t from_where(Move* mv, Board* bo) {
    int64_t possible = get_mask(mv->piece, mv->destination);
    int64_t from_mask = 0;
    switch (bo->turn) {
        case (Color) BLACK:
            from_mask |= bo->black;
            break;
        case (Color) WHITE:
            from_mask |= bo->white;
            break;
    }
    switch (mv->piece) {
        case 'P':
            from_mask &= bo->pawns;
            break;
        case 'R':
            from_mask &= bo->rooks;
            break;
        case 'N':
            from_mask &= bo->knights;
            break;
        case 'B':
            from_mask &= bo->bishops;
            break;
        case 'K':
            from_mask &= bo->kings;
            break;
        case 'Q':
            from_mask &= bo->queens;
            break;
    }
    printbf("from mask:\n", from_mask);
    printbf("getmask:\n", possible);
    from_mask &= possible;
    return from_mask;
}