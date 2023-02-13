/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA4 
* MatrixTest.c 
* Test client for Matrix ADT
* If no errors are raised and all memory is freed then Matrix ADT worked correctly 
*********************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "Matrix.h"

int main(int argc, char* argv[]){
    // test newMatrix
    Matrix A = newMatrix(3);
    Matrix B = newMatrix(3);

    // test size
    assert(size(A) == 3);
    assert(size(B) == 3);

    // test equals
    assert(equals(A, B));

    // test changeEntry
    changeEntry(A, 1, 1, 1.1);
    changeEntry(B, 1, 1, 1.1);
    assert(equals(A, B));
    changeEntry(A, 2, 2, 3.2);
    changeEntry(B, 2, 2, 2.2);
    changeEntry(B, 3, 3, 3.3);

    // test NNZ
    assert(NNZ(A) == 2);
    assert(NNZ(B) == 3);

    // test sum
    Matrix C = sum(A, B);
    printMatrix(stdout, C);

    // test diff
    Matrix D = diff(A, B);
    printMatrix(stdout, D);

    // test product
    Matrix E = product(A, B);
    printMatrix(stdout, E);
    
    // test copy
    Matrix F = copy(A);
    printMatrix(stdout, F);

    // test transpose
    Matrix G = transpose(A);
    printMatrix(stdout, G);

    // test scalarMult
    Matrix H = scalarMult(2, A);
    printMatrix(stdout, H);

    // test freeMatrix
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    return 0;
}


/*
Expected Output:

1: (1, 2.2)
2: (2, 5.4)
3: (3, 3.3)
2: (2, 1.0)
3: (3, -3.3)
1: (1, 1.2)
2: (2, 7.0)
1: (1, 1.1)
2: (2, 3.2)
1: (1, 1.1)
2: (2, 3.2)
1: (1, 2.2)
2: (2, 6.4)
*/
