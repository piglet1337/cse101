/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA5 
* Shuffle.c
* Shuffle program that counts the amount of faro shuffles to return a list to original order
* Usage: Shuffle <largest list size>
*********************************************************************************/ 
//include libraries
#include "List.h"
// #include <chrono>

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

//another method of calculating count
//2^k%(n) = 1 for smallest int k>0, add 1 to n if even.
//this works because we are tracking the first card in the deck.
//when the first card returns back to the top of the deck the rest of the deck is also in orignal order.
//every shuffle a cards index in the deck is doubled.
//unless it is in the second half of the deck in which case I have to (mod n) otherwise it would leave the deck.
//I tested it for first 10,000. Normal method really slows down at that point so I couldn't test it further.
int numShuffles(int n) {
    if (n%2 == 0) {n++;}
    if (n==1) {return 1;}
    //start count at 1 and position of card at 2, because that is the state after the first shuffle, and it is always shuffled at least once.
    int count = 1, cardPosition = 2;
    while (cardPosition != 1) {
        cardPosition = cardPosition*2 % n;
        count++;
    }
    return count;
}

int main(int argc, char *argv[]) {

    // auto start_time = std::chrono::high_resolution_clock::now();

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

        // Normal way of calculating count
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

        // faster way of calculating count
        int count = numShuffles(i);

        // test that they are equal
        // if (count != numShuffles(i)) {
        //     std::cout << "fail";
        //     exit(1);
        // }

        std::cout << "\t\t " + std::to_string(count) + "\n";
    }

    // auto end_time = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    // std::cout << "Time taken: " << duration << " milliseconds" << std::endl;

    return 0;
}