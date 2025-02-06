#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Columns{
    // the left column need to have "B" and the right column have "A"
    char left[100];     //register what there are at the left column
    char right[100];    //register what there are at the right column

    int leftAmount;     //register how many "plates" there are at the left column
    int rightAmount;    //register how many "plates" there are at the right column
};

int decideInitialCondition(int *leftAmount, int *rightAmount, char *left, char *right){
    srand(time(NULL));

    // gen a random number for left. and don't let be 100 or 0
    *leftAmount = ((double)rand() / RAND_MAX) * 100;
    if(*leftAmount == 0)
        *leftAmount = 1;
    else if(*leftAmount == 100)
        *leftAmount = 99;

    // gen a random number for right. and don't let be 100 or 0
    *rightAmount = ((double)rand() / RAND_MAX) * 100;
    if(*rightAmount == 0)
        *rightAmount = 1;
    else if(*rightAmount == 100)
        *rightAmount = 99;


    for(int j = 0; j < 2; j++){
        // says if it will add at the left or right column (or amount)
        char *isLeft;
        int *isLeftA;

        if(j == 0){
            isLeft = left;
            isLeftA = leftAmount;
        };

        if(j == 1){
            isLeft = right;
            isLeftA = rightAmount;
        };

        // gen the plates
        for(int i = 0; i < *isLeftA; i++){
            // if j == 0, the seed is that
            srand(time(NULL) + i);

            // if j == 1, the seed is that
            if(j == 1)
                srand(time(NULL) + i + 100);

            // randomize the characters A or B
            // 0 is B and 1 is A
            char AorB = round( (double)rand() / RAND_MAX ) + 65;

            isLeft[i] = AorB;
        };
    };
};

int main(){
    struct Columns columns;

    /*decideInitialCondition(&columns.leftAmount, &columns.rightAmount, columns.left, columns.right);*/
    return 0;
};

