#ifndef DEFS_H
#define DEFS_H

// unsigned 64-bit integer; can hold a large non-negative integer value (from 0 upto 615)
// used in a chess engine to efficiently represent the positions of pieces, especially the pawns
typedef unsigned long long U64;

#define NAME "Vice 1.0"
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
    int_fiftyMove; // the 50 move rule status at the time
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
} S_BOARD;

#endif //DEFS_H
