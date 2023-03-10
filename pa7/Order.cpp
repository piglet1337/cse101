/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA6 
* Order.c
* Order program that creates and prints a Dictionary
* Usage: Order <input file> <output file>
*********************************************************************************/ 


#include "Dictionary.h"
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    //Print to stderr if more or less than two arguments
    if (argc != 3) {
        fprintf(stderr, "Expected two arguments\n");
        return 1;
    }
    //open input file
    std::ifstream infile(argv[1]);

    //add lines to dictionary
    std::string line;
    Dictionary D = Dictionary();
    valType i = 1;
    while (std::getline(infile, line)) {
        D.setValue(line, i);
        i++;
    }
    infile.close();

    //write output to outfile
    std::ofstream outfile(argv[2]);
    outfile << D.to_string();
    outfile << "\n";
    outfile << D.pre_string();

    return 0;
}