#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "fen.h"
#include "board.h"
/*
    feNo: Forsyth–Edwards Notation
    https://en.wikipedia.org/wiki/Forsyth-Edwards_Notation
    feNo for starting position:          rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w
    FENo (struct) for starting position: RNBQKBNRPPPPPPPP00000000000000000000000000000000pppppppprnbqkbnr
    this is because the bitboard is ordered from a1 to h8

    char* pieces;
    Color turn; // white or black
    char castling; // KQkq would be 0b1111, Qk would be 0b0110, etc.
    int en_passant; // target square of en passant, if any, else "-" the move e4 would be "e3"
    int halfmove; // number of halfmoves since last capture or pawn advance, used for 50 move rule
    int fullmove; // starts at 1, incremented after black moves
*/
// only valid fen notation allowed
struct FEN* parseFEN(char* fen) {
    struct FEN* parsed = (struct FEN*)malloc(sizeof(struct FEN));
    parsed->castling = 0;
    int len = strlen(fen);
    int outputIndex = 0;
    int iter = 0;
    for (int i = 0; i < len; i++) {
        char c = fen[i];
        if (c == ' ') {
            iter++;
            continue;
        }
        switch (iter)
        {
        case 0:
            if (c == '/') {
            // Skip slashes
            } else if (c >= '1' && c <= '8') {
                int numEmptySquares = c - '0';
                for (int j = 0; j < numEmptySquares; j++) {
                    parsed->pieces[outputIndex++] = '0';
                }
            } else {
                parsed->pieces[outputIndex++] = c;
            }
            break;
        
        case 1:
            if (c == 'w') {
                parsed->turn = WHITE;
            } else if (c == 'b') {
                parsed->turn = BLACK;
            } else {
                printf("Invalid turn: %c\n", c);
                exit(1);
            }
            break;
        
        case 2:
            switch (c)
            {
            case 'K':
                parsed->castling |= 0b1000;
                break;
            case 'Q':
                parsed->castling |= 0b0100;
                break;
            case 'k':
                parsed->castling |= 0b0010;
                break;
            case 'q':
                parsed->castling |= 0b0001;
                break;
            default:
                printf("Invalid castling: %c\n", c);
                exit(1);
                break;
            }
            break;
        case 3:
            if (c == '-') {
                parsed->en_passant = -1;
            } else {
                int file = c - 'a';
                int rank = fen[i+1] - '1';
                parsed->en_passant = 8 * rank + file;
                i++;
            }
            break;
        case 4:
            parsed->halfmove = c - '0';
            break;
        case 5:
            parsed->fullmove = c - '0';
            break;
        default:
            printf("Invalid FEN: %s\n", fen);
            exit(1);
            break;
        }
        
    }

    // Null-terminate the output string
    parsed->pieces[outputIndex] = '\0';
    //printf("got here\n");
    //printf("%s\n", parsed->pieces);
    return parsed;
}

void printfen(struct FEN* fen) {
    printf("%s %c %d %d %d %d\n", fen->pieces, fen->turn == WHITE ? 'w' : 'b', fen->castling, fen->en_passant, fen->halfmove, fen->fullmove);
}