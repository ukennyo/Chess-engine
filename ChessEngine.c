#include "stdio.h"
#include "defs.h"

//temp main function to test if bitcount function works through macro
int main (){
    AllInit();
    U64 playBitboard = 0ULL;
    playBitboard |= (1ULL << SQ64(D2));
    playBitboard |= (1ULL << SQ64(D3));
    playBitboard |= (1ULL << SQ64(D4));
    printf("\n");
    printBitboard(playBitboard);
    int count =CNT(playBitboard);
    printf("\n");
    printf("Count: %d\n", count);

    int index = POP(&playBitboard);
    printf("index: %d\n", index);
    printBitboard(playBitboard);
    return 0;
}





//commented out, to test bitboards pop and count functions
/*int main() {
    //Assume that sq120 and sq64 are already initialized
    AllInit(); // added here so main file can find and call the code
    int index =0;
    //to verify array initialization, the arrays are printed to the console
    for(index = 0; index < BRD_SQ_NUM; ++index){ // for loop used to print the sq120 array (our chess board with the borders)
        if(index%10 == 0) printf("\n"); //printf acts as the width specifier for better readabilty
            printf("%5d ", sq120to64[index]); //mod is used to format the output to ensure our numbers are printed in a grid-like structure
    }
    printf("\n");
    printf("\n");
    for(index = 0; index < 64; ++index){ // for loop used to print the sq64 array (our chess board)
        if(index%8==0) printf("\n");
        printf("%5d ", sq64to120[index]);
        }
        return 0;
}
*/
/* commented out code which was used to check if bitboards work as needed:

int main() {
    AllInit();
    U64 playBitboard = 0ULL;
    printf("start\n\n");
    printBitboard(playBitboard);

    playBitboard |= (1ULL << SQ64(D2));
    printf("D2 Added: \n\n");

    printBitboard(playBitboard);


    playBitboard |= (1ULL << SQ64(G2));
    printf("G2 Added: \n\n");
    printBitboard(playBitboard);

       }
    */