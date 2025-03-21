#ifndef DEFS_H
#define DEFS_H
#include "stdlib.h"

//debugging assertions
#define DEBUG
#ifndef DEBUG
#define ASSERT(n)
#else
//Assertion checking is crucial so we know that the moves are made within the boundaries
#define ASSERT(n) if(!(n)) printf("Assertion failed: %s\n", #n); \
printf("On %s "__DATE__); \
printf(" at %s "__TIME__); \
printf(" In File %s "__FILE__); \
printf(" At Line %d "__LINE__); \
exit(1); 
#endif

// unsigned 64-bit integer; can hold a large non-negative integer value (from 0 upto 615)
// used in a chess engine to efficiently represent the positions of pieces, especially the pawns
typedef unsigned long long U64;

#define NAME "ChessEngine 1.0"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVES 2048 //Never seen a chess game go over 1000 moves, so its safe to keep the max number of moves at this number.

//Numerators constants to represent our pieces on the chess board
//Pieces that start with 'w' are the white pieces
//Pieces that start with 'b' are the black pieces
//Chess pieces : Pawn, Knight, Bishop, Rook, Queen, King
enum { EMPTY, wP, wN,  wB, wR, wQ, wK, bP, bN,  bB, bR, bQ, bK };
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };
enum {RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };
enum {WHITE, BLACK, BOTH};
enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};
enum {TRUE, FALSE};
//Castling permissions 
    //the sum value of the values assigned to the castling variables tell you which values can be castled and which cannot be castled
enum {NO_CASTLE, WHITE_KING_CASTLE = 1, WHITE_QUEEN_CASTLE = 2, BLACKKING_CASTLE = 4, BLACK_QUEEN_CASTLE = 8};

// Structure that allows for undoing moves, this can be achieved by creating a structure which stores the history of moves made up until current move
// The structure contains variables which are required make sure the move is perfectly undone
typedef struct {
    int move; // The move to be reverted
    int castlePerm; // the castle permissions before the move was played
    int enPas; // the en passant square, if one was set
    int fiftyMove; // the 50 move rule status at the time
    U64 posKey; // the position of the piece at the time the move was played
    } S_UNDO;
//Board Structure definitions
typedef struct {
    int piece[BRD_SQ_NUM];
    //array named pawns, holds upto 3 'U64' values, which represnet a specific set of pawns
    //pawns[0] represent all white, pawns [1] represent all black, pawns[2] represent all pawns white and black on the board
    U64 pawns[3];

    //KingSq holds two values to store the square number occupied by the black and white king
    int KingSq[2];

    //side shows the current side to move
    int side;

    // the en passant square
    //En passant is a special pawn capture move in chess that can occur immediately after a pawn moves two squares forward from its starting position
    //if the en passant move is used, then enPas is set to NO_SQ
    int enPas;

    //fifty move counter to detect a draw
    int fiftyMove;

    //half moves, in order for our chess engine to figure out what move is the best course of action, our engine searches through a certain number of 'ply' vlaues ahead and evaluates the best potential move.
    //ply value helps manage various move orders and track the progress of the search within a specific variation
    int ply;

    //total number of half-moves made in the game so far, used for detecting threefold repetition(detecting draw, when exact same position appears on the boeard three times during the course of a game)
    int histPly;

    // unique key generated for each position ( U64 format makes the key more unique)
    U64 posKey;

    // stores the number of pieces of each type on the board
    // for example: pceNum[2] would give the number of wite knights on the board, as our second piece listed in our piece list is wN, for white knights on the board
    int pceNum[13];

    //stores the number of non-pawns on the board (black, white and both)
    int bigPce[3];

    //stores the number of rooks and queens for black, white and both
    int majPce[3];

    //stores the number of knights and bishops for black, white and both
    //used in position evaluation, especially during for draw endgames
    //helps determine it a game can be draw based on material combinations
    int minPce[3];

    int casltePerm; //Outputs which sides can be castled, by taking the sum of the numbers (1,2,4,8) assigned to white and black queen and king side's which can be castled
    S_UNDO history[MAXGAMEMOVES]; //Everytime a move is made on the board, we will store the move number which we're at, the move which is about to be made, the castle perms before the move was made, the enpassant status etc.. (also the position key)

    //Piece List
    //piece list is dimensioned as [13][10]
    //the first dimension accounts for 13 chess piece types, in chess programming its common to assign numeric constants to represent piece types
    //for example empty square(0), white pawn(1), white knight(2), white bishop(3), white queen(6) etc and so on...
    //first dimension needs to have enough slots to accomodate all these piece types
    /*13 spaces allows for: 
    - an empty square value
    - 6 white piece types
    - 6 black piece types
    */
   //the second dimension represents the max number of pieces of each type that could possibly appear on a chess board
   //for example, the second dimension is 10, it means we can have a maximum of 10 pieces of a singular piece (ex: white knight)
   //allocating upto 10 slots for each type is necessary to consider the extreme possibilty for max pawn promotions.
   // ex: 2 original white rooks + 8 pawn promotion white rooks = 10 rooks in total
    int pList[13][10];
} S_BOARD;

//MACROS
//Given file and rank, this macro gives us a coordinate to the equivalent square on the 120 square board
#define FR2SQ(f,r) ((21+ (f)) +((r) * 10))
//second macro to convert 120 bit to 64 bit
#define SQ64(sq120) sq120to64[sq120]

//GLOBALS
// Our board is in a 120 square representation to deal with borders, but the bitboard representation uses 64 squares. Because of this we need to be able to convert between 120 based and 64 based indexing.
//to solve this we use two arrays which are defined globally to facilitate the conversion between 120-based and 64-based board indexing
extern int sq120to64[BRD_SQ_NUM]; // maps 120 square to 64 square
extern int sq64to120[64]; // maps 64 square to 120 square
//the above arrays arre declared with the 'extern' keyword, allowing them to be accessed from any file

//FUNCTIONS
//init.c
//function to initialize the board
extern void AllInit(); //from init.c

//bitboards.c
//function to initialize the bitboards
extern void printBitboard(U64 bb); //from bitboards.c
#endif //DEFS_H
