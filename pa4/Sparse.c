/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA4 
* Sparse.c
* Sparse program that does a multitude of matrix operations
* Usage: Sparse <input file> <output file>
*********************************************************************************/ 
//include libraries
#include "Matrix.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //Print to stderr if more or less than two arguments
    if (argc != 3) {
        fprintf(stderr, "Expected two arguments\n");
        return 1;
    }
    //open input and output file
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    //loop through input file
    int size, aLength, bLength;
    fscanf(inputFile, "%d %d %d", &size, &aLength, &bLength);
    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);
    char* buffer = (char*) calloc(2, sizeof(char));
    fgets(buffer, 1, inputFile);
    for (int i = 0; i < aLength; i++) {
        int row, column;
        double x;
        fscanf(inputFile, "%d %d %lf", &row, &column, &x);
        changeEntry(A, row, column, x);
    }
    fgets(buffer, 1, inputFile);
    free(buffer);
    for (int i = 0; i < bLength; i++) {
        int row, column;
        double x;
        fscanf(inputFile, "%d %d %lf", &row, &column, &x);
        changeEntry(B, row, column, x);
    }
    //print Matrices
    fprintf(outputFile, "A has %d non-zero entries:\n", aLength);
    printMatrix(outputFile, A);
    fprintf(outputFile, "\nB has %d non-zero entries:\n", bLength);
    printMatrix(outputFile, B);
    fprintf(outputFile, "\n(1.5)*A =\n");
    Matrix temp = scalarMult(1.5, A);
    printMatrix(outputFile, temp);
    freeMatrix(&temp);

    fprintf(outputFile, "\nA+B =\n");
    temp = sum(A, B);
    printMatrix(outputFile, temp);
    freeMatrix(&temp);

    fprintf(outputFile, "\nA+A =\n");
    temp = sum(A, A);
    printMatrix(outputFile, temp);
    freeMatrix(&temp);

    fprintf(outputFile, "\nB-A =\n");
    temp = diff(B, A);
    printMatrix(outputFile, temp);
    freeMatrix(&temp);

    fprintf(outputFile, "\nA-A =\n");
    temp = diff(A, A);
    printMatrix(outputFile, temp);
    freeMatrix(&temp);

    fprintf(outputFile, "\nTranspose(A) =\n");
    temp = transpose(A);
    printMatrix(outputFile, temp);
    freeMatrix(&temp);

    fprintf(outputFile, "\nA*B =\n");
    temp = product(A, B);
    printMatrix(outputFile, temp);
    freeMatrix(&temp);
    
    fprintf(outputFile, "\nB*B =\n");
    temp = product(B, B);
    printMatrix(outputFile, temp);
    freeMatrix(&temp);
    
    //free memory
    fclose(inputFile);
    fclose(outputFile);
    freeMatrix(&A);
    freeMatrix(&B);

    return 0;
}