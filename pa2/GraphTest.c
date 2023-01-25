/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA2 
* GraphTest.c
* Test case for Graph ADT
*********************************************************************************/ 

//include libraries
#include "Graph.h"
#include <assert.h>
#include <string.h>

int main(int argc, char* argv[]) {
    //test newGraph
    Graph G = newGraph(4);
    //test getOrder
    assert(getOrder(G) == 4);
    //test addEdge
    addEdge(G, 1, 3);
    //test addArc
    addArc(G, 2, 4);
    //test getSize
    assert(getSize(G) == 2);

    //test printGraph
    FILE *tmpFile = tmpfile();
    printGraph(tmpFile, G);
    rewind(tmpFile);
    char line[30];
    fgets(line, 30, tmpFile);
    assert(!strcmp(line, "1: 3 \n"));
    fgets(line, 30, tmpFile);
    assert(!strcmp(line, "2: 4 \n"));
    fgets(line, 30, tmpFile);
    assert(!strcmp(line, "3: 1 \n"));
    fgets(line, 30, tmpFile);
    assert(!strcmp(line, "4: \n"));
    fclose(tmpFile);

    //test freeGraph
    freeGraph(&G);
}
