/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa2
*  GraphTest.c
*  Test client for Graph ADT.
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
  Graph A = newGraph(100);
  List L = newList();
  List  C = newList(); // central vertices
  addArc(A, 64, 4);
          addArc(A, 64, 3);
          addArc(A, 42, 2);
          addArc(A, 2, 64);
          addArc(A, 4, 2);
          addArc(A, 3, 42);
          BFS(A, 3);
          getPath(L, A, 64);
          append(C, 3);
          append(C, 42);
          append(C, 2);
          append(C, 64);
          if (!equals(L, C)) return 0;
          moveFront(L);
          BFS(A, 2);
          getPath(L, A, 2);
          append(C, 2);
          if (!equals(L, C)) return 0;
          getPath(L, A, 99);
          if (equals(L, C)) return 0;
          clear(L);
          clear(C);
          append(C, NIL);
          BFS(A, 99);
          getPath(L, A, 2);
          if (!equals(C, L)) return 0;
          printf("ok");
          return 0;

  int i, s, max, d, n = 35;
  List  P = newList(); // peripheral vertices
  List  E = newList(); // eccentricities
  Graph G = NULL;

  // Build graph G
  G = newGraph(n);

  for(i=1; i<n; i++){
     if( i%7!=0 ) addEdge(G, i, i+1);
     if( i<=28  ) addEdge(G, i, i+7);
  }
  addEdge(G, 9, 31);
  addEdge(G, 17, 13);
  addEdge(G, 14, 33);

  // Calculate the eccentricity of each vertex
  for(s=1; s<=n; s++){
     BFS(G, s);
     max = getDist(G, 1);
     for(i=2; i<=n; i++){
        d = getDist(G, i);
        max = ( max<d ? d : max );
     }
     append(E, max);
  }

  // Free objects
  freeList(&C);
  freeList(&P);
  freeList(&E);
  freeGraph(&G);

  return 0;
}
