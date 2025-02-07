#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Columns{
    // the left column need to have "A" and the right column have "B"
    char left[200];     //register what there are at the left column
    char right[200];    //register what there are at the right column

    int leftAmount;     //register how many "plates" there are at the left column
    int rightAmount;    //register how many "plates" there are at the right column

    char evidence; // can be 'A'(for left column) or 'r'(for right column)
};

int decideInitialCondition(int *leftAmount, int *rightAmount, char *left, char *right, char *evidence){
    srand(time(NULL));

    // gen a random number for left. and don't let be 100 or 0
    /**leftAmount = ((double)rand() / RAND_MAX) * 100;*/
    *leftAmount = 6; // TMP
    if(*leftAmount == 0)
        *leftAmount = 1;
    else if(*leftAmount == 100)
        *leftAmount = 99;

    // gen a random number for right. and don't let be 100 or 0
    /**rightAmount = ((double)rand() / RAND_MAX) * 100;*/
    *rightAmount = 8; // TMP
    if(*rightAmount == 0)
        *rightAmount = 1;
    else if(*rightAmount == 100)
        *rightAmount = 99;


    // this first loop will add the randomize values to *left and *right
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

        // random gen the plates
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
            printf("%c ", isLeft[i]);
        };

        printf("\n");
    };

    // decides the evidence object (the side with less amount of plates)
    if(*leftAmount < *rightAmount)
        *evidence = 'A';

    if(*rightAmount < *leftAmount)
        *evidence = 'B';
};

int main(){
    struct Columns columns;
    decideInitialCondition(
        &columns.leftAmount, 
        &columns.rightAmount, 
        columns.left, 
        columns.right,
        &columns.evidence
    );

    printf("\n================================================");

    int *evidObjAmountP; // evidence object amount pointer
    char *evidObjP; // evidence object pointer
                    //
    int *noEvidObjAmountP; // the opposite of the evidence object amount pointer
    char *noEvidObjP; // the opposite of the evidence object pointer
    
    if(columns.evidence == 'A'){
        evidObjAmountP = &columns.leftAmount;
        evidObjP = columns.left;

        noEvidObjAmountP = &columns.rightAmount;
        noEvidObjP = columns.right;
    };

    if(columns.evidence == 'B'){
        evidObjAmountP = &columns.rightAmount;
        evidObjP = columns.right;

        noEvidObjAmountP = &columns.leftAmount;
        noEvidObjP = columns.left;
    };


    // starts the sequence


    /*the sequece: 
        AAAABA
        AABBABAB
    represents, in columns:
    (LEFT)      (RIGHT)
                B 
                A
    A           B
    B           A
    A           B
    A           B
    A           A
    A           A

    the first in the row mode is the one on bottom, and the last one in the row mode is the one on top
    */


    // move everything of evidence to noEvidence
    for(int i = 0; i < *evidObjAmountP; i++){
        noEvidObjP[*noEvidObjAmountP + i] = evidObjP[i];

        evidObjP[i] = 'N'; // N means nonee
    };

    // say that there's nothing in evidence and how many there's in noEvidence
    *noEvidObjAmountP += *evidObjAmountP;
    *evidObjAmountP = 0;

    return 0;
};

