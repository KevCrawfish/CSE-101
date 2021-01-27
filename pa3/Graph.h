/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa3
*  Graph.h
*  Contains function headers for List.c
*****************************************************************************************/
 #ifndef __GRAPH_H__
 #define __GRAPH_H__

 #include "List.h"

 #define NIL -1
 #define INF 10000

 typedef struct GraphObj *Graph;

 // Creates and returns a new empty graph.
 Graph newGraph(int n);

 // Frees all heap memory associated with *pG, and sets
 // *pG to NULL.
 void freeGraph(Graph* pG);

 // Returns the number of vertices of the graph.
 int getOrder(Graph G);

 // Returns the number of edges of the graph.
 int getSize(Graph G);

 // Returns the source vertex most recently used in function BFS()
 // Returns NIL if BFS() has not yet been called.
 int getSource(Graph G);

 // Returns the parent of vertex u in the Breadth-First tree created by BFS()
 // Returns NIL if BFS() has not yet been called.
 // pre: i <= u <= getOrder(G)
 int getParent(Graph G, int u);

 // Returns the distance from the most recent BFS source to vertex u
 // Returns INF if BFS() has not yet been called.
 // pre: i <= u <= getOrder(G)
 int getDist(Graph G, int u);

 // Appends to the List L the vertices of a shortest path in G from source to u
 // Appends to L the value NIL if no such path exists.
 // pre: getSource(G) != NIL
 // pre: i <= u <= getOrder(G)
 void getPath(List L, Graph G, int u);

 // Returns the discover time from DFS()
 // pre: 1 <= u <= n = getOrder(G)
 int getDiscover(Graph G, int u);

 // Returns the finish time from DFS()
 // pre: 1 <= u <= n = getOrder(G)
 int getFinish(Graph G, int u);

 // Inserts a new edge joining u to v
 // i.e: u is added to the adjacency List of v, and v to the adjacency List of u.
 // pre: Their two int arguments must lie in the range 1 to getOrder(G)
 void addEdge(Graph G, int u, int v);

 // Inserts a new directed edge from u to v
 // i.e: v is added to the adjacency List of u (but not u to the adjacency List of v)
 // pre: Their two int arguments must lie in the range 1 to getOrder(G)
 void addArc(Graph G, int u, int v);

 // Runs the BFA algorithm on the Graph G with source s
 // Sets the color, distance, parent, and source fields of G accordingly.
 void BFS(Graph G, int s);

 // Pre: length(S) == getOrder(G)
 void DFS(Graph G, List S);

 // Returns a reference to a new graph object representing the transpose of G
 Graph transpose(Graph G);

 // Returns a reference to a new graph that is a copy of G
 Graph copyGraph(Graph G);

 // Prints the adjacency list representation of G to the file pointed to by out.
 void printGraph(FILE* out, Graph G);

 #endif
