/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa3
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
  int *discover;
  int *finish;
  int time;
  int vertices; //order
  int edges; //size
  int source;
} GraphObj;

// Creates and returns a new empty graph.
Graph newGraph(int n){
  Graph G = malloc(sizeof(GraphObj));

  G->lists = (List *)malloc((n + 1) * sizeof(List));
  G->colors = (char *)malloc((n + 1) * sizeof(char));
  G->parents = (int *)malloc((n + 1) * sizeof(int));
  G->distance = (int *)malloc((n + 1) * sizeof(int));
  G->discover = (int *)malloc((n + 1) * sizeof(int));
  G->finish = (int *)malloc((n + 1) * sizeof(int));
  for(int i = 1; i < n + 1; i++){
    G->lists[i] = newList();
    G->parents[i] = NIL;
    G->distance[i] = INF;
    G->discover[i] = 0;
    G->finish[i] = 0;
  }

  G->vertices = n;
  G->edges = 0;
  G->time = 0;
  G->source = NIL;
  return G;
}

// Frees all heap memory associated with *pG, and sets
// *pG to NULL.
void freeGraph(Graph* pG){
  if(pG != NULL && *pG != NULL){
    for(int i = 1; i < (*pG)->vertices + 1; i++) {
      freeList(&(*pG)->lists[i]);
    }
    free((*pG)->finish);
    free((*pG)->discover);
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
  if (G == NULL){
    printf("Graph Error: calling getSource() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->source;
}

// Returns the parent of vertex u in the Breadth-First tree created by BFS()
// Returns NIL if BFS() has not yet been called.
// pre: i <= u <= getOrder(G)
int getParent(Graph G, int u){
  if (G == NULL){
    printf("Graph Error: calling getSource() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(G->parents[u] == NIL){
    return 0;
  }
  return G->parents[u];
}

// Returns the distance from the most recent BFS source to vertex u
// Returns INF if BFS() has not yet been called.
// pre: i <= u <= getOrder(G)
int getDist(Graph G, int u){
  if (G == NULL){
    printf("Graph Error: calling getSource() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->distance[u];
}

// Appends to the List L the vertices of a shortest path in G from source to u
// Appends to L the value NIL if no such path exists.
// pre: getSource(G) != NIL
// pre: i <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
  if (G == NULL){
    printf("Graph Error: calling getpath() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if(getSource(G) == NIL){
    printf("Graph Error: calling getpath() with no source\n");
    exit(EXIT_FAILURE);
  }
  if(u == getSource(G)){
    append(L, getSource(G));
  } else if (G->parents[u] == NIL){
    append(L, NIL);
  } else{
    getPath(L, G, G->parents[u]);
    append(L, u);
  }
}

// Returns the discover time from DFS()
// pre: 1 <= u <= n = getOrder(G)
int getDiscover(Graph G, int u){
  if (G == NULL){
    printf("Graph Error: calling getDiscover() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->discover[u];
}

// Returns the finish time from DFS()
// pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u){
  if (G == NULL){
    printf("Graph Error: calling getFinish() on NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return G->finish[u];
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
  G->source = s;
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
  int y = 0;
  while(length(Q) > 0){
    x = front(Q);
    deleteFront(Q);
    for(moveFront(G->lists[x]); index(G->lists[x])>=0; moveNext(G->lists[x])){
      y = get(G->lists[x]);
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

// Performs the depth first search algorithm on G
// Defines the order in which vertices are to be processed in the main loop of DFS
// Stores the vertices by decreasing finish times.
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S){
  if(length(S) != getOrder(G)){
    printf("Graph Error: calling DFS() while List S != vertices of G\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i <= G->vertices; i++){
    G->colors[i] = 'w';
    G->parents[i] = NIL;
  }
  G->time = 0;
  for(int i = 1; i <= G->vertices; i++){
    if(G->colors[i] == 'w'){
      visit(G, i);
    }
  }

  int array[length(S) + 1];
  for(int i = 1; i <= G->vertices; i++){
    array[i] = i;
  }

  for(int i = 1; i <= G->vertices; i++){
    for(int j = 1; j <= G->vertices; j++){
      if(G->finish[array[j]] < G->finish[array[i]]){
        int tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
      }
    }
  }
  clear(S);
  for(int i = 1; i <= G->vertices; i++){
    append(S, array[i]);
  }
}

void visit(Graph G, int x){
  G->discover[x] = ++(G->time);
  G->colors[x] = 'g';
  for(moveFront(G->lists[x]); index(G->lists[x])>=0; moveNext(G->lists[x])){
    int y = get(G->lists[x]);
    if(G->colors[y] == 'w'){
      G->parents[y] = x;
      visit(G, y);
    }
  }
  G->colors[x] = 'b';
  G->finish[x] = ++(G->time);
}

// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
  if(G == NULL){
    printf("Graph Error: calling printGraph() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  for(int i = 1; i < G->vertices + 1; i++){
    fprintf(out, "%d: ", i);
    printList(out, G->lists[i]);
    fprintf(out, "\n");
  }
}

// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G){
  Graph R = newGraph(G->vertices);

  if(G == NULL){
    printf("List Error: calling copyGraph() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i <= G->vertices; i++){
    for(moveFront(G->lists[i]); index(G->lists[i])>=0; moveNext(G->lists[i])){
      addArc(R, get(G->lists[i]), i);
    }
  }

  return R;
}

// Returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G){
  Graph R = newGraph(G->vertices);

  if(G == NULL){
    printf("List Error: calling copyGraph() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 1; i <= G->vertices; i++){
    for(moveFront(G->lists[i]); index(G->lists[i])>=0; moveNext(G->lists[i])){
      addArc(R, i, get(G->lists[i]));
    }
  }

  return R;
}
