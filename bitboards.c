#include "stdio.h"
#include "defs.h"
//this array is unordered due to a technical reason related to the 'PopBit' function.
//this bittable is used mainly by the 'popBit' function to efficiently find the position of a set bit ('1' bit) in the bitboard
//array is not in sequential order because it doesnt represent the positions directly, instead its structured to help with a specific bit manupilation technique called 'de Bruijin sequence" multiplication 
const int BitTable[64] = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 
    61, 29, 2, 51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 
    1, 40, 4, 49, 5, 52, 26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 
    48, 24, 59, 14, 12, 55, 38, 28, 58, 20, 37, 17, 36, 8
};
//functions of popBit:
//returns the index (0-63) of the least significant bit that is set to 1 in a bitboard
//sets that bit to 0, effectively "removing" it from the bitboard

int PopBit(U64 *bb) {
     U64 b = *bb ^ (*bb -1);
     unsigned int fold  = (unsigned) ((b & 0xffffffff) ^ (b >> 32));
     *bb &= (*bb -1);
     return BitTable[(fold * 0x783a9b23) >> 26];
}
// CountBits function counts and returns the number of bits that are set to 1 in a bitboard
// Helpful when you need to know how many pieces of a certain type are on the board
int CountBits(U64 b){
    int r;
    for (r = 0; b; r++, b &= b - 1);
    return r;
}
//prints the bitboard 
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