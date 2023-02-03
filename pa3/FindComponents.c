/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA3 
* FindComponents.c
* FindComponents program that finds the strong components of a graph
* Usage: FindComponents <input file> <output file>
*********************************************************************************/ 
//include libraries
#include "Graph.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //Print to stderr if more or less than two arguments
    if (argc != 3) {
        fprintf(stderr, "Expected two arguments\n");
        return 1;
    }
    //open input and output file
    FILE *inputFile = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");

    //loop through input file
    int order, u, v;
    fscanf(inputFile, "%d", &order);
    Graph G = newGraph(order);
    while (1) {
        fscanf(inputFile, "%d %d", &u, &v);
        if (u == 0 && v == 0) {break;}
        addArc(G, u, v);
    }
    fprintf(outputFile, "Adjacency list representation of G:\n");
    printGraph(outputFile, G);

    // Run DFS on G and transpose of G
    Graph T = transpose(G);
    List S = newList();
    for(int i=1; i<=order; i++) append(S, i);
    DFS(G, S);
    DFS(T, S);
    // count number of components
    int numComponents = 0;
    for (moveFront(S); index(S) >= 0; moveNext(S)) {
        if (getParent(T, get(S)) == 0) {
            numComponents++;
        }
    }
    fprintf(outputFile, "\nG contains %d strongly connected components:", numComponents);
    // make and print component lists
    List *components = (List *) calloc(numComponents, sizeof(List));
    int component = 0;
    for (moveFront(S); index(S) >= 0; moveNext(S)) {
        if (getParent(T, get(S)) == 0) {
            components[component] = newList();
            component++;
        }
        append(components[component-1], get(S));
    }
    for (int i = component - 1; i >= 0; i--) {
        fprintf(outputFile, "\nComponent %d: ", component - i);
        printList(outputFile, components[i]);
        freeList(&components[i]);
    }
    // free memory
    free(components);
    fclose(inputFile);
    fclose(outputFile);
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    return 0;
}