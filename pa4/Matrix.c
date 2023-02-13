/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA4 
* Matrix.c 
* Matrix ADT Module 
*********************************************************************************/ 
//include libraries
#include "Matrix.h"
#include <stdlib.h>

typedef struct EntryObj* Entry;
typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

// newEntry()
// returns a new entry with value and column
static Entry newEntry(int column, double value) {
    Entry E = (Entry) malloc(sizeof(EntryObj));
    E->column = column;
    E->value = value;
    return E;
}
// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix m = (Matrix) malloc(sizeof(MatrixObj));
    m->size = n;
    m->entryArrray = (List *) calloc(n, sizeof(List));
    for (int i = 0; i < n; i++) {
        m->entryArrray[i] = newList();
    }
    return m;
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    for (int i = 0; i < (*pM)->size; i++) {
        freeList(&(*pM)->entryArrray[i]);
    }
    free((*pM)->entryArrray);
    free(*pM);
    *pM = NULL;
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    return M->size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    int total = 0;
    for (int i = 0; i < size(M); i++) {
        total += length(M->entryArrray[i]);
    }
    return total;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if (NNZ(A) != NNZ(B) || A->size != B->size) {return 0;}
    for (int i = 0; i < A->size; i++) {
        moveFront(A->entryArrray[i]);
        moveFront(B->entryArrray[i]);
        if (length(A->entryArrray[i]) != length(A->entryArrray[i])) {return 0;}
        while (index(A->entryArrray[i]) >= 0) {
            Entry aEntry = (Entry) get(A->entryArrray[i]);
            Entry bEntry = (Entry) get(B->entryArrray[i]);
            if (aEntry->column != bEntry->column || aEntry->value != bEntry->value) {return 0;}
            moveNext(A->entryArrray[i]);
            moveNext(B->entryArrray[i]);
        }
    }
    return 1;
}
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    for (int i = 0; i < M->size; i++) {
        clear(M->entryArrray[i]);
    }
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (i<1 || i>size(M) || j<1 || j>size(M) || x == 0) {return;}
    Entry changed = newEntry(j, x);
    for (moveFront(M->entryArrray[i-1]); index(M->entryArrray[i-1]) >= 0; moveNext(M->entryArrray[i-1])) {
        Entry current = (Entry) get(M->entryArrray[i-1]);
        if (current->column == j) {
            set(M->entryArrray[i-1], changed);
            return;
        }
        if (current->column > j) {
            insertBefore(M->entryArrray[i-1], changed);
            return;
        }
    }
    append(M->entryArrray[i-1], changed);
}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    Matrix copy = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        for (moveFront(A->entryArrray[i]); index(A->entryArrray[i]) >= 0; moveNext(A->entryArrray[i])) {
            Entry current = (Entry) get(A->entryArrray[i]);
            changeEntry(copy, i+1, current->column, current->value);
        }
    }
    return copy;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    Matrix transpose = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        for (moveFront(A->entryArrray[i]); index(A->entryArrray[i]) >= 0; moveNext(A->entryArrray[i])) {
            Entry current = (Entry) get(A->entryArrray[i]);
            changeEntry(transpose, current->column, i+1, current->value);
        }
    }
    return transpose;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    Matrix scalar = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        for (moveFront(A->entryArrray[i]); index(A->entryArrray[i]) >= 0; moveNext(A->entryArrray[i])) {
            Entry current = (Entry) get(A->entryArrray[i]);
            changeEntry(scalar, i+1, current->column, current->value*x);
        }
    }
    return scalar;
}
static List listSum(List A, List B, int sum) {
    List L = newList();
    moveFront(A);
    moveFront(B);
    while (index(A) >= 0 && index(B) >= 0) {
        Entry aCurrent = (Entry) get(A);
        Entry bCurrent = (Entry) get(B);
        if (aCurrent->column == bCurrent->column) {
            if (sum) {
                if (aCurrent->value+bCurrent->value != 0) {
                    append(L, newEntry(aCurrent->column, aCurrent->value+bCurrent->value));
                }
            }
            else {if (aCurrent->value-bCurrent->value != 0) {append(L, newEntry(aCurrent->column, aCurrent->value-bCurrent->value));}}
            moveNext(A);
            moveNext(B);
        }
        if (aCurrent->column > bCurrent->column) {
            if (sum)  {
                append(L, bCurrent);
            }
            else {append(L, newEntry(bCurrent->column, -bCurrent->value));}
            moveNext(B);
        }
        if (aCurrent->column < bCurrent->column) {
            append(L, aCurrent);
            moveNext(A);
        }
    }
    while(index(A) >= 0) {
        Entry aCurrent = (Entry) get(A);
        append(L, aCurrent);
        moveNext(A);
    }
    while(index(B) >= 0) {
        Entry bCurrent = (Entry) get(B);
        append(L, bCurrent);
        moveNext(B);
    }
    return L;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {exit(1);}
    Matrix sum = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        sum->entryArrray[i] = listSum(A->entryArrray[i], B->entryArrray[i], 1);
    }
    return sum;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {exit(1);}
    Matrix diff = newMatrix(A->size);
    for (int i = 0; i < A->size; i++) {
        diff->entryArrray[i] = listSum(A->entryArrray[i], B->entryArrray[i], 0);
    }
    return diff;
}

static double vectorDot(List P, List Q) {
    double total = 0;
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0) {
        Entry pCurrent = (Entry) get(P);
        Entry qCurrent = (Entry) get(Q);
        if (pCurrent->column == qCurrent->column) {
            total += pCurrent->value * qCurrent->value;
            moveNext(Q);
            moveNext(P);
        }
        if (pCurrent->column > qCurrent->column) {
            moveNext(Q);
        }
        if (pCurrent->column < qCurrent->column) {
            moveNext(P);
        }
    }
    return total;
}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (size(A) != size(B)) {exit(1);}
    Matrix AB = newMatrix(size(A));
    Matrix trans = transpose(B);
    for (int i = 0; i < size(A); i++) {
        for (int j = 0; j < size(trans); j++) {
            changeEntry(AB, i+1, j+1, vectorDot(A->entryArrray[i], trans->entryArrray[j]));
        }
    }
    return AB;
}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    for (int i = 0; i < M->size; i++) {
        if (length(M->entryArrray[i]) == 0) {continue;}
        fprintf(out, "%d:", i+1);
        for (moveFront(M->entryArrray[i]); index(M->entryArrray[i]) >= 0; moveNext(M->entryArrray[i])) {
            Entry current = (Entry) get(M->entryArrray[i]);
            fprintf(out, " (%d, %.1f)", current->column, current->value);
        }
        fprintf(out, "\n");
    }
}
