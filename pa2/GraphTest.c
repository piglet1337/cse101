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
    Graph G = newGraph(5);
    //test getOrder
    assert(getOrder(G) == 5);
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

    //test makeNULL
    makeNull(G);

    //test BFS
    addEdge(G, 1, 4);
    addEdge(G, 2, 4);
    addEdge(G, 2, 3);
    addEdge(G, 3, 4);
    BFS(G, 1);

    //test getSource
    assert(getSource(G) == 1);

    //test getParent
    assert(getParent(G, 3) == 4);
    assert(getParent(G, 2) == 4);
    assert(getParent(G, 4) == 1);
    assert(getParent(G, 1) == NIL);

    //test getDist
    assert(getDist(G, 3) == 2);
    assert(getDist(G, 2) == 2);
    assert(getDist(G, 4) == 1);
    assert(getDist(G, 1) == 0);

    //test getPath
    List path = newList();
    getPath(path, G, 3);
    moveFront(path);
    assert(get(path) == 1);
    moveNext(path);
    assert(get(path) == 4);
    moveNext(path);
    assert(get(path) == 3);
    clear(path);
    getPath(path, G, 5);
    moveFront(path);
    assert(get(path) == NIL);
    freeList(&path);
    
    //test freeGraph
    freeGraph(&G);
}
