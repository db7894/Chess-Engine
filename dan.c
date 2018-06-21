// dan.c

#include "stdio.h"
#include "stdlib.h"
#include "defs.h"

int main() {

    AllInit();
    int index = 0;
    U64 playBitBoard = 0ULL;

    // for(index = 0; index < 64; ++index) {
    //     printf("Index:%d\n",index);
    //     PrintBitBoard(SetMask[index]);
    //     printf("\n");
    // }

    // int index = 0;
    //
    // for(index = 0; index < BRD_SQ_NUM; ++index) {
    //     if(index&10==0) printf("\n");
    //     printf("%5d",Sq120ToSq64[index]);
    // }
    //
    // printf("\n");
    // printf("\n");
    //
    // for(index = 0; index < 64; ++index) {
    //     if(index%8==0) printf("\n");
    //     printf("%5d",Sq64ToSq120[index]); //%5 is width specifier
    // }

    return 0;
}
