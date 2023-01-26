/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA2 
* FindPath.c
* FindPath program that finds path between vertices in given graph
* Usage: Lex <input file> <output file>
*********************************************************************************/ 
//include libraries
#include "Graph.h"

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
        addEdge(G, u, v);
    }
    printGraph(outputFile, G);
    while (1) {
        fscanf(inputFile, "%d %d", &u, &v);
        if (u == 0 && v == 0) {break;}
        List path = newList();
        BFS(G, u);
        getPath(path, G, v);
        if (getDist(G, v) == INF) {
            fprintf(outputFile, "\nThe distance from %d to %d is infinity\nNo %d-%d path exists", u, v, u, v);
        }
        else {
            fprintf(outputFile, "\nThe distance from %d to %d is %d\nA shortest %d-%d path is: ", u, v, getDist(G, v), u, v);
            printList(outputFile, path);
        }
        fprintf(outputFile, "\n");
        freeList(&path);
    }
    freeGraph(&G);
    fclose(inputFile);
    fclose(outputFile);
}
