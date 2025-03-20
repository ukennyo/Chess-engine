#include "stdio.h"
#include "defs.h"

void printBitboard(U64 bb) {
    U64 shiftMe = 1ULL;
    int rank, file, sq, sq64 = 0;
    printf("\n");

    //nested for loop to traverse through each square on the board print out our bit values in the correct order(in order of file and rank)
    for(rank =RANK_8; rank>= RANK_1; --rank) {
        for(file = FILE_A; file <= FILE_H; ++file){
            sq = FR2SQ(file, rank); //square index (120 based index)
            sq64 = SQ64(sq); //64 bit index conversion using the second macro defined in header file; you get the value assigned to each square in a 64 bit format

            //how do we assign values based on whether if theres a piece on a particular square on the board?
            /* if shifting one ULL by the 64 based index (sq64) and our bitwise AND'ed with our bitboard gives us a non-zero value, then we know that there was a bit on our particular square
            If there WAS a value on that square then we print X to show its occupied
            else print minus to show its vacant
            */
            if((shiftMe << sq64) & bb) printf("X");
            else printf("-");

        }
        printf("\n");
    }
    printf("\n\n");
}