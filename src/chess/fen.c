#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "fen.h"


void zeroFen(Fen* fen) {
    //memset(fen->pieces, '\0', sizeof(fen->pieces));
    fen->turn       = WHITE;
    fen->castling   = 0;
    fen->en_passant = -1;
    fen->halfmove   = 0;
    fen->fullmove   = 1;
    fen->pieces[64] = '\0';
}

// Takes a Fen* and a fen string and puts all data in the struct
Fen* parseFen(char* fen_str) {
    Fen* my_fen = (Fen*) malloc((int) sizeof(Fen));
    zeroFen(my_fen);
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
                break;
            } else if (c >= '1' && c <= '8') {
                int emptySq = c - '0';
                for (int j = 0; j < emptySq; j++) {
                    my_fen->pieces[out_index] = '0';
                    out_index++;
                }
            } else {
                my_fen->pieces[out_index] = c;
                out_index++;
            }

            break;

        case 1:
            if (c == 'w')
                my_fen->turn = WHITE;
            else if (c == 'b')
                my_fen->turn = BLACK;
            else
                exit(-1);
            break;

        case 2:
            switch (c) {
            
            case 'K':
                my_fen->castling |= 0b1000;
                break;
            case 'Q':
                my_fen->castling |= 0b0100;
                break;
            case 'k':
                my_fen->castling |= 0b0010;
                break;
            case 'q':
                my_fen->castling |= 0b0001;
                break;
            default:
                exit(-1);
                break;
            }
            break;
        case 3:
            if (c == '-')
                my_fen->en_passant = -1;
            else { // this is lowkey genious
                int file = c - 'a';
                int rank = fen_str[i+1] - '1';
                my_fen->en_passant = 8 * rank + file;
                i++;
            }
            break;
        case 4:
            my_fen->halfmove = c - '0';
            break;
        case 5:
            my_fen->fullmove = c - '0';
            break;
        default:
            exit(-1);
            break;
        }
    }
    //my_fen->pieces[out_index] = '\0'; // probably redundant;
    return my_fen;
}

void printFen(Fen* fen) {
    printf("%s %c %d %d %d %d\n", fen->pieces, fen->turn == WHITE ? 'w' : 'b', fen->castling, fen->en_passant, fen->halfmove, fen->fullmove);
}
