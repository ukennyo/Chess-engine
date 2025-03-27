// File to handle initialization tasks
#include "defs.h"
#include "stdlib.h"
//macro used to generate a random 64 bit number
//below comments explain visually how it works
//all it's doing is filling 64 bits with random numbers 
// 0000 000000000000000 000000000000000 000000000000000 111111111111111  when rand generates a random number, it generates a 15 bit random number, so we split it into 4 parts to make it for 64 bits we have available
// 0000 000000000000000 000000000000000 111111111111111 000000000000000 
// 0000 000000000000000 111111111111111 000000000000000 000000000000000
// 0000 111111111111111 000000000000000 000000000000000 000000000000000 
// 1111 000000000000000 000000000000000 000000000000000 000000000000000 // bitwise AND the last 15 bits random number and shift by 60 to fill the last 4 bits
#define RAND_64 (           (U64)rand() + \                 
                            (U64)rand() << 15 + \           
                            (U64)rand() << 30 + \           
                            (U64)rand() << 45 + \           
                            ((U64)rand() & 0xf) << 60     ) 
int sq64to120[64];
int sq120to64[BRD_SQ_NUM];

U64 SetMask[64]; //array used to set a specific bit in a bitboard
U64 ClearMask[64]; //array used to clear a specific bit from bitboard

U64 PieceKeys[13][120]; //explain these
U64 SideKey;
U64 CastleKeys[16];

void InitHashKeys(){

    int index = 0;
    int index2 = 0; 
    for(index = 0; index < 13; ++index){
        for(index2 = 0; index2 < 120; ++index2){
            PieceKeys[index][index2] = RAND_64;
        }
    }
    SideKey = RAND_64;
    for(index =0; index <16; ++index){
    CastleKeys[index] = RAND_64;
    }

}

void InitBitMasks(){ //where set and clear masks are initialized
    int index = 0;
    for (index = 0; index < 64; index++) {// index value is first set to 0
        SetMask[index] = 0ULL;
        ClearMask[index] = 0ULL;
    }
    for (index = 0; index < 64; index++) {
        SetMask[index] |= (1ULL << index); //each element at index is set to 1 unsigned long long is shifted left by 'index' positions (this sets 'index' bit to 1)
        ClearMask[index] = ~SetMask[index]; //each element at 'index' is set to the complement of its corresponding setMask value (~ denotes bitwise complement)
    }
}

// Initialization function to initialize the 120 and 64 conversion arrays.
void InitializeSq120to64(){
    // we use two types of arrays here for square mapping
    // one is for 64x64 (our standard chess board size) and the other is 120x120 (used for easier boundary checks)
    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;
    //Initialize both arrays with impossible values for error checking
    //these impossible values act as a fail-safe, helping to identify errors during array usage
    for(index = 0; index < BRD_SQ_NUM; ++index) {
        sq120to64[index] = 65; //invalid value
    }
    for(index =0; index < 64; ++index){
        sq64to120[index] = 120; //invalid value
    }
    //Loop through each square on the board, converting each square to its 64-bit equivalent
    //
    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            sq =FR2SQ(file, rank); //calculates the 120-based index using the FR2SQ macro in header file
            //square mapping is implemented through looping each file (column) and rank (row) and calculating the square index (FR2SQ) to convert file and rank to a square index
            sq64to120[sq64] =sq; //maps each of the 64 squares to its corresponding spot in the 120-square array
            sq120to64[sq] = sq64; //maps each of the 120 squares to its corresponding spot in the 64-square array
            sq64++; // index for the 64 square array, is incremented by one per loop iteration to mirror the 0-63 index of the 64 square array.
        }
    }
}    

void AllInit() {
    InitializeSq120to64();
    InitBitMasks();
}
