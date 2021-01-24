/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa2
*  GraphTest.c
*  Test client for Graph ADT.
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
  int i, s, max, d, n = 35;
  List  C = newList(); // central vertices
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

  // Print adjacency list representation of G
  printGraph(stdout, G);

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
