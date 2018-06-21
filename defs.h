#ifndef DEFS_H
#define DEFS_H

#include "stdlib.h"
#include "stdio.h"

#define DEBUG


// if debug defined, define assert.
// if n false, print to the screen what failed, etc.
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif

typedef unsigned long long U64;

#define NAME "Dan 1.0"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVES 2048

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" // FEN notation for starting chessboard pos

//w - white, b - black
enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bR, bQ, bK };
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };

enum { WHITE, BLACK, BOTH };

enum {
  A1 = 21, B1, C1, D1, E1, F1, G1, H1,
  A2 = 31, B2, C2, D2, E2, F2, G2, H2,
  A3 = 41, B3, C3, D3, E3, F3, G3, H3,
  A4 = 51, B4, C4, D4, E4, F4, G4, H4,
  A5 = 61, B5, C5, D5, E5, F5, G5, H5,
  A6 = 71, B6, C6, D6, E6, F6, G6, H6,
  A7 = 81, B7, C7, D7, E7, F7, G7, H7,
  A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
};

enum { FALSE, TRUE };

//        0 0 0 0 (bit 1 tells us whether white king can castle). all 0s means none can castle
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 }; //white king castlinng, etc.

typedef struct {

    int move;
    int castlePerm; //castle permission
    int enPas;
    int fiftyMove;
    U64 posKey;

} S_UNDO;

typedef struct {
    int pieces[BRD_SQ_NUM];

    // in 64-sq rep, array that indexes 0-63.
    // pawn at A2: set a bit to 1. to set this bit (A2 has val of 8),
    // take 1 and shift it 8 times
    U64 pawns[3]; //bit set to 1 if pawn of corresp color on the square
    // ex, if 01000000 rep A1 to H1, there's a pawn theere

    int KingSq[2];

    int side; // current side
    int enPas; //if en passant
    int fiftyMove; //counter, if hit 50 gm drawn

    int ply; //halfmoves for curr search
    int hisPly; // how many half moves made in  game

    int castlePerm;

    U64 posKey;

    int pcsNum[13]; //# pieces on board, indexed by piece type
    int bigPcs[3]; // store by color, # of "big pieces"  (not pawns)
    int majPcs[3]; //queen, king
    int minPcs[3];

    S_UNDO history[MAXGAMEMOVES]; // each time a move is made, store all important vars here

    // piece list
    int pList[13][10]; //13 piece types, up to 10 on the board at any one time

    // white knight: pList[wN][0] = E1;
    // add knight to D4: pList[wN][1] = D4;...
} S_BOARD;

/* MACROS */

//the macro below, when given file/rank #, returns 120-array based num/sq
#define FR2SQ(f,r) ( (21 + (f) ) + ( (r) * 10 ) )
#define SQ64(sq120) (Sq120ToSq64[(sq120)])
#define SQ120(sq64) (Sq64ToSq120[(sq64)])
#define POP(b) PopBit(b)
#define CNT(b) CountBits(b)
#define CLRBIT(bb,sq) ((bb) &= ClearMask[ (sq) ])
#define SETBIT(bb,sq) ((bb) != SetMask[ (sq) ])

/* GLOBALS */

extern int Sq120ToSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 SetMask[64];
extern U64 ClearMask[64];
U64 PieceKeys[13][120];
U64 SideKey;
U64 CastleKeys[16];

/* FUNCTIONS */

// init.c
extern void AllInit();

// bitboards.c
extern void PrintBitBoard(U64 bb);
extern int PopBit(U64 *bb);
extern int CountBits(U64 b);

// hashkeys.c
extern U64 GeneratePosKey(const S_BOARD *pos);

// board.c
extern void ResetBoard(S_BOARD *pos);

#endif
