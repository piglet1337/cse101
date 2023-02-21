/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA5 
* Shuffle.c
* Shuffle program that counts the amount of faro shuffles to return a list to original order
* Usage: Shuffle <largest list size>
*********************************************************************************/ 
//include libraries
#include "List.h"

//another method of calculating count
//2^k%(n+1) = 1 for smallest int k>0
int numShuffles(int n) {
    if (n%2 == 1) {n--;}
    if (n==0) {return 1;}
    long count = 1, k = 2;
    while (k != 1) {
        k *= 2;
        k %= n+1;
        count++;
    }
    return count;
}

//Performs a faro shuffle on D
void shuffle(List& D) {
    List temp;
    int size = D.length();
    D.moveFront();
    for (int i = 0; i < size/2; i++) {
        temp.insertBefore(D.front());
        D.eraseAfter();
    }
    D.moveFront();
    temp.moveFront();
    while (temp.length() > 0) {
        D.moveNext();
        D.insertBefore(temp.front());
        temp.eraseAfter();
    }
}

int main(int argc, char *argv[]) {
    //Print to stderr if more or less than one argument
    if (argc != 2) {
        fprintf(stderr, "Expected one argument\n");
        return 1;
    }
    //get largest from inputted argument
    int largest = atoi(argv[1]);
    //Print formattiong
    std::cout << "deck size       shuffle count\n------------------------------\n";
    //Print size and amount of shuffles from 1 to largest
    for (int i = 1; i < largest+1; i++) {
        std::cout << " " + std::to_string(i);
        // List L;
        // for (int j = 0; j < i; j++) {
        //     L.insertBefore(j);
        // }
        // int count = 1;
        // List copy = List(L);
        // shuffle(L);
        // while (!(copy == L)) {
        //     shuffle(L);
        //     count++;
        // }
        int count = numShuffles(i);
        // if (count != numShuffles(i)) {std::cout << "fail";}
        std::cout << "\t\t " + std::to_string(count) + "\n";
    }
    return 0;
}