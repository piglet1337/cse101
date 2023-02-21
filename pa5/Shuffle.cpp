/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA5 
* Shuffle.c
* Shuffle program that counts the amount of faro shuffles to return a list to original order
* Usage: Shuffle <largest list size>
*********************************************************************************/ 
//include libraries
#include "List.h"

void shuffle(List& D) {
    
}

int main(int argc, char *argv[]) {
    //Print to stderr if more or less than two arguments
    if (argc != 2) {
        fprintf(stderr, "Expected one argument\n");
        return 1;
    }
    int largest = atoi(argv[1]);
    List L;
    for (int i = 0; i < largest; i++) {
        L.insertBefore(i);
    }
    std::cout << L.to_string();
}