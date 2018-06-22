// init.c

#include "defs.h"
#include "stdio.h"
#include "stdlib.h"

// explanation for below is here: https://www.youtube.com/watch?v=WqVwQBXLwE0&index=12&list=PLZ1QII7yudbc-Ky058TEaOstZHVbT-2hg
#define RAND_64 (     (U64)rand() | \
                      (U64)rand() << 15 | \
                      (U64)rand() << 30 | \
                      (U64)rand() << 45 | \
                      ( (U64)rand() & 0xf) << 60  )

int Sq120ToSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120];
U64 SideKey; // hash in a random # if white to move
U64 CastleKeys[16]; // recall castle allowances

void InitHashKeys() {
    int index = 0;
    int index2 = 0;
    for(index = 0; index < 13; ++index) {
        for(index2 = 0; index2 < 120; ++index2) {
            PieceKeys[index][index2] = RAND_64;
        }
    }
    SideKey = RAND_64;
    for(index = 0; index < 16; ++index) {
        CastleKeys[index] = RAND_64;
    }
}

void InitBitMasks() {
    int index = 0;

    for(index = 0; index < 64; ++index) {
        SetMask[index] = 0ULL;
        ClearMask[index] = 0ULL;
    }

    for(index = 0; index < 64; ++index) {
          SetMask[index] |= (1ULL << index);
          ClearMask[index] = ~SetMask[index]; //bitwise complement
    }
}

void InitSq120To64() {

    int index = 0;
    int file = FILE_A;
    int rank = RANK_1;
    int sq = A1;
    int sq64 = 0;
    for(index = 0; index < BRD_SQ_NUM; ++index) {
        Sq120ToSq64[index] = 65; //set everything to 65
    }

    for(index = 0; index < 64; ++index) {
        Sq64ToSq120[index] = 120; // go from 64-120 and return impossible value
    }

    for(rank = RANK_1; rank <= RANK_8; ++rank) {
        for(file = FILE_A; file <= FILE_H; ++file) {
            // step thru in order of indexes in array
            // if set sq64 to 0, increment each time sets everything to index
            sq = FR2SQ(file,rank); // get square
            Sq64ToSq120[sq64] = sq; // set this at index of sq64
            Sq120ToSq64[sq] = sq64; // set this as our current square
            sq64++; // increment
        }
    }
}

void AllInit() {
    InitSq120To64();
    InitBitMasks();
    InitHashKeys();
}
