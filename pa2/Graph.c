/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa2
*  Graph.c
*  Graph ADT implementation.
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

// private GraphObj type
typedef struct GraphObj{
  int *lists;
  int *colors;
  int *parents;
  int *distance;
  int order;
  int edges;
} GraphObj;

// Creates and returns a new empty graph.
Graph newGraph(int n){
  return 0;
}

// Frees all heap memory associated with *pG, and sets
// *pG to NULL.
void freeGraph(Graph* pG){

}

// Returns the number of vertices of the graph.
int getOrder(Graph G){
  return 0;
}

// Returns the number of edges of the graph.
int getSize(Graph G){
  return 0;
}

// Returns the source vertex most recently used in function BFS()
// Returns NIL if BFS() has not yet been called.
int getSource(Graph G){
  return 0;
}

// Returns the parent of vertex u in the Breadth-First tree created by BFS()
// Returns NIL if BFS() has not yet been called.
// pre: i <= u <= getOrder(G)
int getParent(Graph G, int u){
  return 0;
}

// Returns the distance from the most recent BFS source to vertex u
// Returns INF if BFS() has not yet been called.
// pre: i <= u <= getOrder(G)
int getDist(Graph G, int u){
  return 0;
}

// Appends to the List L the vertices of a shortest path in G from source to u
// Appends to L the value NIL if no such path exists.
// pre: getSource(G) != NIL
// pre: i <= u <= getOrder(G)
void getPath(List L, Graph G, int u){

}

// deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G){

}

// Inserts a new edge joining u to v
// i.e: u is added to the adjacency List of v, and v to the adjacency List of u.
// pre: Their two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){

}

// Inserts a new directed edge from u to v
// i.e: v is added to the adjacency List of u (but not u to the adjacency List of v)
// pre: Their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v){

}

// Runs the BFA algorithm on the Graph G with source s
// Sets the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s){

}

// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){

}
