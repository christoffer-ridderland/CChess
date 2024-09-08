#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "fen.h"


void zeroFen(Fen* fen) {
    memset(fen->pieces, '\0', sizeof(fen->pieces));
    fen->turn       = WHITE;
    fen->castling   = 0;
    fen->en_passant = -1;
    fen->halfmove   = 0;
    fen->fullmove   = 1;
}

// Takes a Fen* and a fen string and puts all data in the struct
void parseFen(char* fen_str, Fen* fen) {
    zeroFen(fen);
    int length = strlen(fen_str);
    int out_index = 0;
    int field = 0;
    for (int i = 0; i < length; i++) {
        char c = fen_str[i];
        if (c == ' ') {
            field++;
            continue;
        }
        switch (field) {
        case 0:
            if (c == '/') {
            } else if (c >= '1' && c <= '8') {
                int emptySq = c - '0';
                for (int j = 0; j < emptySq; j++) {
                    fen->pieces[out_index++] = '0';
                }
            } else {
                fen->pieces[out_index++] = c;
            }
            break;

        case 1:
            if (c == 'w')
                fen->turn = WHITE;
            else if (c == 'b')
                fen->turn = BLACK;
            else
                exit(-1);
            break;

        case 2:
            switch (c) {
            
            case 'K':
                fen->castling |= 0b1000;
                break;
            case 'Q':
                fen->castling |= 0b0100;
                break;
            case 'k':
                fen->castling |= 0b0010;
                break;
            case 'q':
                fen->castling |= 0b0001;
                break;
            default:
                exit(-1);
                break;
            }
            break;
        case 3:
            if (c == '-')
                fen->en_passant = -1;
            else { // this is lowkey genious
                int file = c - 'a';
                int rank = fen_str[i+1] - '1';
                fen->en_passant = 8 * rank + file;
                i++;
            }
            break;
        case 4:
            fen->halfmove = c - '0';
            break;
        case 5:
            fen->fullmove = c - '0';
            break;
        default:
            exit(-1);
            break;
        }
    }
    fen->pieces[out_index] = '\0'; // probably redundant;
}

void printFen(Fen* fen) {
    printf("%s %c %d %d %d %d\n", fen->pieces, fen->turn == WHITE ? 'w' : 'b', fen->castling, fen->en_passant, fen->halfmove, fen->fullmove);
}
