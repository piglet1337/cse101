/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA5 
* ListTest.cpp 
* Test client for List ADT
* If no errors are raised and all memory is freed then List ADT worked correctly 
*********************************************************************************/ 

#include "List.h"
#include <assert.h>
#include <chrono>

int main() {
    List L;

    //test moveFront
    L.moveFront();
    //test insertAfter and insertBefore
    L.insertAfter(1);
    L.insertBefore(2);
    //test front, back, and length
    assert(L.front() == 2);
    assert(L.back() == 1);
    assert(L.length() == 2);
    L.insertBefore(3);
    //test position
    assert(L.position() == 2);
    //test moveNext and movePrev
    L.moveNext();
    assert(L.position() == 3);
    L.movePrev();
    assert(L.position() == 2);
    //test peekNext and peekPrev
    assert(L.peekNext() == 1);
    assert(L.peekPrev() == 3);
    //test moveBack
    L.moveBack();
    assert(L.position() == 3);
    //test List Copy
    List copy = List(L);
    //test equals and clear
    assert(copy == L);
    copy.clear();
    assert(!(copy == L));
    //test setBefore and setAfter
    L.movePrev();
    L.setBefore(4);
    L.setAfter(5);
    assert(L.peekNext() == 5);
    assert(L.peekPrev() == 4);
    //test eraseBefore
    L.eraseBefore();
    assert(L.peekNext() == 5);
    assert(L.peekPrev() == 2);
    assert(L.length() == 2);
    //test findNext and findPrev
    L.moveFront();
    assert(L.findNext(5) == 2);
    assert(L.findPrev(5) == 1);
    assert(L.findPrev(5) == -1);
    assert(L.findNext(14) == -1);
    assert(L.position() == L.length());
    //test concat
    copy.insertAfter(6);
    List concat = L.concat(copy);
    assert(concat.position() == 0);
    assert(concat.to_string() == "(2, 5, 6)");
    //test cleanup
    List cleanup = List();
    for (int i = 0; i < 10; i++) {
        cleanup.insertAfter(i);
        cleanup.insertAfter(i);
    }
    cleanup.moveFront();
    cleanup.moveNext();
    cleanup.moveNext();
    cleanup.cleanup();
    assert(cleanup.to_string() == "(9, 8, 7, 6, 5, 4, 3, 2, 1, 0)");
    assert(cleanup.position() == 1);

    //test function performance
    // List test = List();
    // for (int i = 0; i < 1000; i++) {
    //     test.insertAfter(i);
    // }
    // for (int i = 9; i >= 0; i--) {
    //     test.insertAfter(i);
    // }

    // std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now(); // Get start time

    // for (int i = 0; i < 1000000; i++) {
    //     List copy = test;
    // }

    // std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now(); // Get stop time

    // std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); // Calculate duration in milliseconds

    // std::cout << "Time taken by program: " << duration.count() << " milliseconds" << std::endl;
    return 0;
}