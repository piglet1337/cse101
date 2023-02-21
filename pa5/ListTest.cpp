/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA5 
* ListTest.cpp 
* Test client for List ADT
* If no errors are raised and all memory is freed then List ADT worked correctly 
*********************************************************************************/ 

#include "List.h"
#include <assert.h>

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
    //test concat
    copy.insertAfter(6);
    List concat = L.concat(copy);
    assert(concat.position() == 0);
    // assert(concat.position() == 0);
    assert(concat.to_string() == "(2, 5, 6)");
    return 0;
}