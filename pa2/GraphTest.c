/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa2
*  GraphTest.c
*  Test client for Graph ADT.
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
  int n = 35;
  List  C = newList(); // central vertices
  List  P = newList(); // peripheral vertices
  List  E = newList(); // eccentricities
  Graph G = NULL;

  // Build graph G
  G = newGraph(n);

  // Free objects
  freeList(&C);
  freeList(&P);
  freeList(&E);
  freeGraph(&G);

  return 0;
}
