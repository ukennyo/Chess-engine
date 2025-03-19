## Chess-engine
Chess Engine using C
Main file: ChessEngine.c
Header File defs.h
Makefile compiles ChessEngine.c to ChessEngine.exe

## Board Representation
# Structure
- The board is contained within a structure
- The board is represented by an array of integers
-  Each integer in the array has a value indicating: an empty square, a piece on the square and whether or not the square is off the board

# Coordinates
The chess board coordinates consist of Files (Letters A-H) and Ranks (Numbers 1-8)
The way the moves are represented through these coordinates, rely using algebraic coordinate notation

## Problem with using a simple 8x8 array
- A simple array of 64 integers(8x8) is insufficient for move generation
- Determining when a piece has run off to the edge of the board is difficult
# A fix to counter this problem
- I made the array larger than 8x8
- Added border coordinates around the edges of the board and defined them with a value indicating "off-board"
- When move generation occurs and the move hits a border coordinate, the overall move generation stops for that particular direction

## Special move generation chess piece; The Knight (Issues)
- Knights can move two squares in one direction and one square in another.
- A single row of "off board" squares isn't deep enough to stop knight moves that jump beyond the border.
- Without two rows on the top and bottom, a knight could jump to an out-of-bounds index in the array.
## Side Borders
- Protective rows are only needed on the top and bottom, not the sides.
- Side moves will land on an "off board" square with a value defined as such.
- The extra row on the sides is enough to stop side-moving pieces; the double row at the top and bottom protects against knight jumps. This approach optimizes the array size while ensuring all out-of-bounds moves are caught.

## Position Structure
# Required Elements
- 50-Move Rule Counter: Keeps track of moves since the last capture or pawn move. If 50 moves occur without either, the game is a draw.
- Unique Key: A unique value for the current position to detect threefold repetition (a draw).
- En Passant Square: Keeps track of available en passant captures.
- Side to Move: Indicates whose turn it is (white or black).
- Ply: The number of half-moves made in the game.

