/********************************************************************************* 
* Ryan Miller, rnmiller
* 2023 Winter CSE101 PA1 
* Lex.c 
* Lex program that sorts lines in input file and places them in output file
* Usage: Lex <input file> <output file>
*********************************************************************************/ 
//include libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

int main(int argc, char *argv[]) {
    //Print to stderr if more or less than two arguments
    if (argc != 3) {
        fprintf(stderr, "Expected two arguments");
        return 1;
    }
    //open input and output file
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");
    //initiliaze variables
    int lines = 1;
    int counter = 0;
    int longest = 0;
    //while end of file is not reached
    while (!feof(inputFile)) {
        //get next character and incremet counter
        char character = fgetc(inputFile);
        counter++;
        //if end of line reached
        if (character == '\n') {
            //save longest line
            if (counter > longest) {longest = counter;}
            counter = 0;
            //keep track of number of lines
            lines++;
        }
    }
    //reset stream of input file
    rewind(inputFile);
    //fill array with lines of file
    char **arrayoflines = (char**) calloc(lines, sizeof(char*));
    for (int i = 0; i < lines; i++) {
        arrayoflines[i] = (char*) calloc(longest, sizeof(char));
        if (fgets(arrayoflines[i], longest+2, inputFile) == NULL) {
            printf("test: %d\n", i);
        }
    }
    strcat(arrayoflines[lines-1], "\n");
    //create new list
    List listoflines = newList();
    //loop through lines
    for (int i = 0; i < lines; i++) {
        //if first line apend it to list
        if (length(listoflines) == 0) {
            append(listoflines, i);
        }
        //otherwise insert line into list before the first greater line
        else {
            for (moveFront(listoflines); index(listoflines) >= 0; moveNext(listoflines)) {
                if (strcmp(arrayoflines[get(listoflines)], arrayoflines[i]) > 0) {
                    insertBefore(listoflines, i);
                    break;
                }
                if (index(listoflines) == i - 1) {
                    append(listoflines, i);
                }
            }
        }
    }
    //print lines to output file
    for (moveFront(listoflines); index(listoflines) >= 0; moveNext(listoflines)) {
        fputs(arrayoflines[get(listoflines)], outputFile);
    }
    //free memory
    fclose(inputFile);
    fclose(outputFile);
    freeList(&listoflines);
    for (int i = 0; i < lines; i++) {
        free(arrayoflines[i]);
    }
    free(arrayoflines);
}
