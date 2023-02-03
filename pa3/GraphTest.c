/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA3 
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

    //test copy and transpose graph
    Graph C = copyGraph(transpose(transpose(G)));

    //test DFS
    addArc(C, 5, 3);
    List S = newList();
    append(S, 1);
    append(S, 2);
    append(S, 3);
    append(S, 4);
    append(S, 5);
    DFS(C, S);

    //test getParent
    assert(getParent(C, 1) == NIL);
    assert(getParent(C, 2) == NIL);
    assert(getParent(C, 3) == 1);
    assert(getParent(C, 4) == 2);
    assert(getParent(C, 5) == NIL);

    //test getDiscover
    assert(getDiscover(C, 1) == 1);
    assert(getDiscover(C, 2) == 5);
    assert(getDiscover(C, 3) == 2);
    assert(getDiscover(C, 4) == 6);
    assert(getDiscover(C, 5) == 9);

    //test getFinish
    assert(getFinish(C, 1) == 4);
    assert(getFinish(C, 2) == 8);
    assert(getFinish(C, 3) == 3);
    assert(getFinish(C, 4) == 7);
    assert(getFinish(C, 5) == 10);
    
    //test freeGraph
    freeGraph(&G);
    return 0;
}
