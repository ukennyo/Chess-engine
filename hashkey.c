//hashkeys.c (position keys)
#include "defs.h"
//position key is a unique number representing the position on the chessboard
// to generate a unique key, each piece on the board is assigned to a random value using an array index. The key is then created by XOR'ing these random values together
