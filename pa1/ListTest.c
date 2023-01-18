/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA1 
* ListTest.c 
* Test client for List ADT
* If no errors are raised and all memory is freed then List ADT worked correctly 
*********************************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "List.h"

int main(int argc, char* argv[]){
    //construct lists
    List A = newList();
    List B = newList();
    List C = NULL;

    //Fill Lists with values
    for (int i = 0; i < 10; i++) {
        //test append and prepend
        append(A, i);
        prepend(B, i);
    }

    //test copyList
    C = copyList(A);

    //test length
    assert(length(A) == 10);
    assert(length(B) == 10);
    assert(length(C) == 10);

    //test front
    assert(front(A) == 0);
    assert(front(B) == 9);
    assert(front(C) == 0);

    //test back
    assert(back(A) == 9);
    assert(back(B) == 0);
    assert(back(C) == 9);

    //test deleteFront
    deleteFront(A);
    deleteFront(B);
    deleteFront(C);
    assert(length(A) == 9);
    assert(length(B) == 9);
    assert(length(C) == 9);
    assert(front(A) == 1);
    assert(front(B) == 8);
    assert(front(C) == 1);

    //test deleteBack
    deleteBack(A);
    deleteBack(B);
    deleteBack(C);
    assert(length(A) == 8);
    assert(length(B) == 8);
    assert(length(C) == 8);
    assert(back(A) == 8);
    assert(back(B) == 1);
    assert(back(C) == 8);

    //test equals
    assert(equals(A, C));
    assert(!equals(A, B));

    //test clear
    clear(C);
    assert(length(C) == 0);

    //test moveFront
    moveFront(A);

    //test moveBack
    moveBack(B);

    //test index
    assert(index(A) == 0);
    assert(index(B) == 7);

    //test get
    assert(get(A) == 1);
    assert(get(B) == 1);

    //test movePrev
    movePrev(B);
    assert(index(B) == 6);
    assert(get(B) == 2);

    //test moveNext
    moveNext(A);
    assert(index(A) == 1);
    assert(get(A) == 2);

    //test set
    set(A, 10);
    set(B, 10);
    assert(get(A) == 10);
    assert(get(B) == 10);

    //test insertBefore
    insertBefore(A, 11);
    assert(length(A) == 9);
    movePrev(A);
    assert(get(A) == 11);

    //test insertAfter
    insertAfter(B, 11);
    assert(length(B) == 9);
    moveNext(B);
    assert(get(B) == 11);

    //test delete
    movePrev(B);
    movePrev(B);
    delete(B);
    assert(index(B) == -1);
    assert(length(B) == 8);
    moveFront(B);
    delete(B);
    assert(index(B) == -1);
    assert(length(B) == 7);
    moveBack(B);
    delete(B);
    assert(index(B) == -1);
    assert(length(B) == 6);

    //test movePrev and moveNext off of list
    moveFront(A);
    assert(index(A) == 0);
    movePrev(A);
    assert(index(A) == -1);
    moveBack(A);
    assert(index(A) == 8);
    moveNext(A);
    assert(index(A) == -1);

    //test printList
    FILE *tmpFile = tmpfile();
    printList(tmpFile, A);
    fprintf(tmpFile, "\n");
    printList(tmpFile, B);
    fprintf(tmpFile, "\n");
    rewind(tmpFile);
    char line[30];
    fgets(line, 30, tmpFile);
    assert(!strcmp(line, "1 11 10 3 4 5 6 7 8 \n"));
    fgets(line, 30, tmpFile);
    assert(!strcmp(line, "7 6 5 4 10 11 \n"));
    fclose(tmpFile);

    //test delete on List with 1 item
    append(C, 1);
    moveFront(C);
    delete(C);
    assert(length(C) == 0);

    //test freeList
    freeList(&A);
    freeList(&B);
    freeList(&C);
}