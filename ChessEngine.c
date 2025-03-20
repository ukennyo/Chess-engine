#include "stdio.h"
#include "defs.h"

int main() {
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