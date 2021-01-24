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
  List *lists;
  char *colors;
  int *parents;
  int *distance;
  int vertices; //order
  int edges; //size
  int source;
} GraphObj;

// Creates and returns a new empty graph.
Graph newGraph(int n){
  Graph G = malloc(sizeof(GraphObj));

  G->lists = (List *)malloc((n + 1) * sizeof(List));
  for(int i = 1; i < n + 1; i++){
    G->lists[i] = newList();
  }

  G->colors = (char *)malloc((n + 1) * sizeof(char));
  G->parents = (int *)malloc((n + 1) * sizeof(int));
  G->distance = (int *)malloc((n + 1) * sizeof(int));

  G->vertices = n;
  G->edges = 0;
  G->source = 0;
  return G;
}

// Frees all heap memory associated with *pG, and sets
// *pG to NULL.
void freeGraph(Graph* pG){
  if(pG != NULL && *pG != NULL){
    for(int i = 1; i < (*pG)->vertices + 1; i++) {
      freeList(&(*pG)->lists[i]);
    }
    free((*pG)->lists);
    free((*pG)->colors);
    free((*pG)->parents);
    free((*pG)->distance);
    free(*pG);
    *pG = NULL;
  }
}

// Returns the number of vertices of the graph.
int getOrder(Graph G){
  if (G == NULL){
    printf("Graph Error: calling getOrder() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->vertices;
}

// Returns the number of edges of the graph.
int getSize(Graph G){
  if (G == NULL){
    printf("Graph Error: calling getSize() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->edges;
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
  addArc(G, u, v);
  addArc(G, v, u);
  G->edges--;
}

// Inserts a new directed edge from u to v
// i.e: v is added to the adjacency List of u (but not u to the adjacency List of v)
// pre: Their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v){
  if (G == NULL){
    printf("Graph Error: calling addArc() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
    printf("Graph Error: int arguments outside of range 1 to getOrder(G)\n");
    exit(EXIT_FAILURE);
  }
  if(length(G->lists[u]) > 0){
    moveBack(G->lists[u]);
    while(index(G->lists[u]) >= 0){
      if(v > get(G->lists[u])){
        insertAfter(G->lists[u], v);
        break;
      } else {
        movePrev(G->lists[u]);
      }
      if(index(G->lists[u]) < 0){
        prepend(G->lists[u], v);
        break;
      }
    }
  } else {
    append(G->lists[u], v);
  }

  G->edges++;
}

// Runs the BFA algorithm on the Graph G with source s
// Sets the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s){
  for(int i = 1; i < G->vertices + 1; i++){
    if(i == s){
      continue;
    }
    G->colors[i] = 'w';
    G->distance[i] = INF;
    G->parents[i] = NIL;
  }
  G->colors[s] = 'g';
  G->distance[s] = 0;
  G->parents[s] = NIL;

  List Q = newList();
  append(Q, s);
  int x = 0;
  while(index(Q) > 0){
    x = front(Q);
    deleteFront(Q);
    for(int y = 1; y < G->vertices + 1; y++){
      if(G->colors[y] == 'w'){
        G->colors[y] = 'g';
        G->distance[y] = G->distance[x] + 1;
        G->parents[y] = x;
        append(Q, y);
      }
    }
    G->colors[x] = 'b';
  }
  freeList(&Q);
}

// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
  if(G == NULL){
    printf("Graph Error: calling printGraph() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  for(int i = 1; i < G->vertices + 1; i++){
    printf("%d: ", i);
    printList(out, G->lists[i]);
    printf("\n");
  }
}
