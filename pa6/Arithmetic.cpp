/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA6 
* Arithmetic.c
* Arithmetic program that does different arithmetic on inputed values
* Usage: Arithmetic <input file> <output file>
*********************************************************************************/ 

#include "BigInteger.h"
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    //Print to stderr if more or less than two arguments
    if (argc != 3) {
        fprintf(stderr, "Expected two arguments\n");
        return 1;
    }
    //open input and output file
    std::ifstream infile(argv[1]);

    std::string aString, bString;
    std::getline(infile, aString);
    std::getline(infile, bString);
    std::getline(infile, bString);
    infile.close();

    BigInteger A = BigInteger(aString);
    BigInteger B = BigInteger(bString);

    std::ofstream outfile(argv[2]);

    outfile << A.to_string() + "\n\n";
    outfile << B.to_string() + "\n\n";
    outfile << (A+B).to_string() + "\n\n";
    outfile << (A-B).to_string() + "\n\n";
    outfile << (A-A).to_string() + "\n\n";
    outfile << (BigInteger("3")*A-BigInteger("2")*B).to_string() + "\n\n";
    outfile << (A*B).to_string() + "\n\n";
    outfile << (A*A).to_string() + "\n\n";
    outfile << (B*B).to_string() + "\n\n";
    outfile << (BigInteger("9")*A*A*A*A+BigInteger("16")*B*B*B*B*B).to_string() + "\n\n";
    return 0;
}