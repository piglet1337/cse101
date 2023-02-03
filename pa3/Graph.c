/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA3
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
    int *discover;
    int *finish;
    int order;
    int size;
} GraphObj;

// Constructors-Destructors
Graph newGraph(int n) {
    // returns a Graph pointing to a newly created GraphObj representing a graph having
    // n vertices and no edges. 
    Graph G = (Graph) malloc(sizeof(GraphObj));
    G->adjacencyList = (List *) calloc(n+1, sizeof(List));
    G->colors = (int *) calloc(n+1, sizeof(int));
    G->parents = (int *) calloc(n+1, sizeof(int));
    G->discover = (int *) calloc(n+1, sizeof(int));
    G->finish = (int *) calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    for (int i = 1; i < n + 1; i++) {
        G->adjacencyList[i] = newList();
        G->colors[i] = WHITE;
        G->parents[i] = 0;
        G->discover[i] = NIL;
        G->finish[i] = NIL;
    }
    return G;
}
void freeGraph(Graph* pG) {
    //frees all heap memory associated with Graph *pG and sets *pG to NULL
    free((*pG)->colors);
    free((*pG)->parents);
    free((*pG)->discover);
    free((*pG)->finish);
    for (int i = 1; i < (*pG)->order + 1; i++) {
        freeList(&(*pG)->adjacencyList[i]);
    }
    free((*pG)->adjacencyList);
    free(*pG);
    *pG = NULL;
}
// Access functions
int getOrder(Graph G) {
    // returns order of G
    return G->order;
}
int getSize(Graph G) {
    // returns size of G
    return G->size;
}
int getParent(Graph G, int u) {
    // return parent of vertex u in BFS tree
    if (u < 1 || u > getOrder(G)) {return NIL;}
    return G->parents[u];
}
int getDiscover(Graph G, int u) {
    // return discover time of u
    if (u < 1 || u > getOrder(G)) {return NIL;}
    return G->discover[u];
}
int getFinish(Graph G, int u) {
    // return finish time of u
    if (u < 1 || u > getOrder(G)) {return NIL;}
    return G->finish[u];
}
// Manipulation procedures
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
static int dfsVisit(Graph G, List S, int x, int time) {
    G->discover[x] = ++time;
    G->colors[x] = GRAY;
    for (moveFront(G->adjacencyList[x]); index(G->adjacencyList[x]) >= 0; moveNext(G->adjacencyList[x])) {
        if (G->colors[get(G->adjacencyList[x])] == WHITE) {
            G->parents[get(G->adjacencyList[x])] = x;
            time = dfsVisit(G, S, get(G->adjacencyList[x]), time);
        }
    }
    G->colors[x] = BLACK;
    G->finish[x] = ++time;
    prepend(S, x);
    return time;
}
void DFS(Graph G, List S) {
    // does a Depth First Search on G
    if (length(S) != getOrder(G)) {return;}
    for (int i = 1; i < getOrder(G) + 1; i++) {
        G->colors[i] = WHITE;
        G->parents[i] = 0;
    }
    int time = 0;
    for (moveFront(S); index(S) >= 0; moveNext(S)) {
        if (G->colors[get(S)] == WHITE) {
            time = dfsVisit(G, S, get(S), time);
        }
    }
    for (int i = 0; i < getOrder(G); i++) {
        deleteBack(S);
    }
}
// Other Functions
Graph transpose(Graph G) {
    // returns the transpose of G
    Graph T = newGraph(getOrder(G));
    for (int i = 1; i < getOrder(G) + 1; i++) {
        for (moveFront(G->adjacencyList[i]); index(G->adjacencyList[i]) >= 0; moveNext(G->adjacencyList[i])) {
            addArc(T, get(G->adjacencyList[i]), i);
        }
    }
    return T;
}
Graph copyGraph(Graph G) {
    // returns a copy of G
    Graph C = newGraph(getOrder(G));
    for (int i = 1; i < getOrder(G) + 1; i++) {
        for (moveFront(G->adjacencyList[i]); index(G->adjacencyList[i]) >= 0; moveNext(G->adjacencyList[i])) {
            addArc(C, i, get(G->adjacencyList[i]));
        }
    }
    return C;
}
void printGraph(FILE* out, Graph G) {
    // prints out adjacency list of G to out
    for (int i = 1; i < getOrder(G) + 1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjacencyList[i]);
        fprintf(out, "\n");
    }
}


