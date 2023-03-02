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
    BigInteger A;
    BigInteger B = BigInteger("-98378923");
    BigInteger C = BigInteger(B);
    std::cout << C.to_string();
    return 0;
}