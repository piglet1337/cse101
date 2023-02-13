/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA4 
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
    List C = newList();

    int X[] = {0,1,2,3,4,5,6,7,8,9,10,11};
    //Fill Lists with values
    for (int i = 0; i < 10; i++) {
        //test append and prepend
        append(A, &X[i]);
        append(C, &X[i]);
        prepend(B, &X[i]);
    }

    //test length
    assert(length(A) == 10);
    assert(length(B) == 10);

    //test front
    assert(*(int*)front(A) == 0);
    assert(*(int*)front(B) == 9);

    //test back
    assert(*(int*)back(A) == 9);
    assert(*(int*)back(B) == 0);

    //test deleteFront
    deleteFront(A);
    deleteFront(B);
    assert(length(A) == 9);
    assert(length(B) == 9);
    assert(*(int*)front(A) == 1);
    assert(*(int*)front(B) == 8);

    //test deleteBack
    deleteBack(A);
    deleteBack(B);
    assert(length(A) == 8);
    assert(length(B) == 8);
    assert(*(int*)back(A) == 8);
    assert(*(int*)back(B) == 1);

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
    assert(*(int*)get(A) == 1);
    assert(*(int*)get(B) == 1);

    //test movePrev
    movePrev(B);
    assert(index(B) == 6);
    assert(*(int*)get(B) == 2);

    //test moveNext
    moveNext(A);
    assert(index(A) == 1);
    assert(*(int*)get(A) == 2);

    //test set
    set(A, &X[10]);
    set(B, &X[10]);
    assert(*(int*)get(A) == 10);
    assert(*(int*)get(B) == 10);

    //test insertBefore
    insertBefore(A, &X[11]);
    assert(length(A) == 9);
    movePrev(A);
    assert(*(int*)get(A) == 11);

    //test insertAfter
    insertAfter(B, &X[11]);
    assert(length(B) == 9);
    moveNext(B);
    assert(*(int*)get(B) == 11);

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

    //test delete on List with 1 item
    append(C, &X[1]);
    moveFront(C);
    delete(C);
    assert(length(C) == 0);
    assert(index(C) == -1);
    append(C, &X[1]);
    deleteFront(C);
    assert(length(C) == 0);
    assert(index(C) == -1);
    append(C, &X[1]);
    deleteBack(C);
    assert(length(C) == 0);
    assert(index(C) == -1);

    //test freeList
    freeList(&A);
    freeList(&B);
    freeList(&C);
}