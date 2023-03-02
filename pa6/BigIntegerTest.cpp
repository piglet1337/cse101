/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA6 
* BigIntegerTest.cpp 
* Test client for BigInteger ADT
* If no errors are raised and all memory is freed then List ADT worked correctly 
*********************************************************************************/ 

#include "BigInteger.h"
#include <assert.h>

int main() {
    BigInteger A = BigInteger("1782");
    BigInteger B = BigInteger("2643");
    BigInteger C = BigInteger(B);

    //test compare
    assert(A < B);
    assert(B == C);
    assert(B > A);

    //test add and sub
    assert((A+B).to_string() == "4425");
    assert((B-C).to_string() == "0");
    assert((B-A).to_string() == "861");
    assert((A-B).to_string() == "-861");
    
    //test mult
    A *= B * A;
    assert(A.to_string() == "8392909932");

    //test makeZero
    B.makeZero();
    A *= B;
    assert(A.to_string() == "0");
    assert(B.to_string() == "0");
    return 0;
}