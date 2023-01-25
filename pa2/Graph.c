/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA2 
* Graph.c
* Graph ADT
*********************************************************************************/ 

//include libraries
#include "Graph.h"
#include <stdlib.h>

//define GraphObj struct
typedef struct GraphObj {
    List *adjacencyList;
    int *colors;
    int *parents;
    int *distance;
    int order;
    int size;
    int source;
} GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
    // returns a Graph pointing to a newly created GraphObj representing a graph having
    // n vertices and no edges. 
    Graph G = (Graph) malloc(sizeof(GraphObj));
    G->adjacencyList = (List *) calloc(n+1, sizeof(List));
    G->colors = (int *) calloc(n+1, sizeof(int));
    G->parents = (int *) calloc(n+1, sizeof(int));
    G->distance = (int *) calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for (int i = 1; i < n + 1; i++) {
        G->adjacencyList[i] = newList();
        G->colors[i] = WHITE;
        G->parents[i] = NIL;
        G->distance[i] = INF;
    }
    return G;
}
void freeGraph(Graph* pG) {
    //frees all heap memory associated with Graph *pG and sets *pG to NULL
    free((*pG)->colors);
    free((*pG)->parents);
    free((*pG)->distance);
    for (int i = 1; i < (*pG)->order + 1; i++) {
        freeList(&(*pG)->adjacencyList[i]);
    }
    free((*pG)->adjacencyList);
    free(*pG);
    *pG = NULL;
}
/*** Access functions ***/
int getOrder(Graph G) {
    // returns order of G
    return G->order;
}
int getSize(Graph G) {
    // returns size of G
    return G->size;
}
int getSource(Graph G) {
    // returns source vertex most recently used in BFS()
    return G->source;
}
int getParent(Graph G, int u) {
    // return parent of vertex u in BFS tree
    if (u < 1 || u > getOrder(G)) {return NIL;}
    return G->parents[u];
}
int getDist(Graph G, int u) {
    // return distance between most recent source from BFS to u
    if (u < 1 || u > getOrder(G)) {return NIL;}
    return G->distance[u];
}
void getPath(List L, Graph G, int u) {
    // appends to List L the vertices of a shortest path in G from source to u
    if (u < 1 || u > getOrder(G) || getSource(G) == NIL) {return;}
    if (getParent(G, u) == NIL) {
        append(L, NIL);
        return;
    }
    int vert = u;
    while (vert != getSource(G)) {
        append(L, vert);
        vert = getParent(G, vert);
    }
    append(L, vert);
}
/*** Manipulation procedures ***/
void makeNull(Graph G) {
    // deletes all edges in G
    for (int i = 1; i < getOrder(G) + 1; i++) {
        clear(G->adjacencyList[i]);
    }
    G->size = 0;
}
void addEdge(Graph G, int u, int v) {
    // adds edge between u and v in G
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {return;}
    G->size++;
    // add v to adjacencyList[u]
    for (moveFront(G->adjacencyList[u]); index(G->adjacencyList[u]) >= 0; moveNext(G->adjacencyList[u])) {
        if (get(G->adjacencyList[u]) > v) {
            insertBefore(G->adjacencyList[u], v);
            break;
        }
    }
    if (index(G->adjacencyList[u]) < 0) {append(G->adjacencyList[u], v);}
    // add u to adjacencyList[v]
    for (moveFront(G->adjacencyList[v]); index(G->adjacencyList[v]) >= 0; moveNext(G->adjacencyList[v])) {
        if (get(G->adjacencyList[v]) > u) {
            insertBefore(G->adjacencyList[v], u);
            break;
        }
    }
    if (index(G->adjacencyList[v]) < 0) {append(G->adjacencyList[v], u);}
}
void addArc(Graph G, int u, int v) {
    // adds arc going from u to v
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {return;}
    G->size++;
    // add v to adjacencyList[u]
    for (moveFront(G->adjacencyList[u]); index(G->adjacencyList[u]) >= 0; moveNext(G->adjacencyList[u])) {
        if (get(G->adjacencyList[u]) > v) {
            insertBefore(G->adjacencyList[u], v);
            break;
        }
    }
    if (index(G->adjacencyList[u]) < 0) {append(G->adjacencyList[u], v);}
}
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
    // prints out adjacency list of G to out
    for (int i = 1; i < getOrder(G) + 1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjacencyList[i]);
        fprintf(out, "\n");
    }
}

