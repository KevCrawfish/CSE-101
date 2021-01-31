/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa3
*  GraphTest.c
*  Test client for Graph ADT.
*****************************************************************************************/
#include<stdio.h>
#include <stdint.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){

  int i, n= 8;
  List S = newList();
  Graph G = newGraph(n);

  for(i=1; i<=n; i++) prepend(S, i);

  addArc(G, 2,1);
  addEdge(G, 2,3);
  addArc(G, 4,3);
  addEdge(G, 4,8);
  addArc(G, 5,1);
  addEdge(G, 5,2);
  addArc(G, 5,6);
  addEdge(G, 6,2);
  addArc(G, 6,3);
  addEdge(G, 7,3);
  addArc(G, 7,6);
  addEdge(G, 7,8);
  addArc(G, 8,3);

  printf("This is the Original Graph:\n");
  DFS(G, S);
  printGraph(stdout, G);
  printf("Order: %d\nSize: %d\n", getOrder(G), getSize(G));
  printf("\n");
  fprintf(stdout, "x:  d  f  p\n");
  for(i=1; i<=n; i++){
     fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
  }
  printf("\n\n");

  printf("This is the Transposed Graph:\n");
  Graph T = transpose(G);
  DFS(T, S);
  printGraph(stdout, T);
  printf("Order: %d\nSize: %d\n", getOrder(T), getSize(T));
  printf("\n");
  fprintf(stdout, "x:  d  f  p\n");
  for(i=1; i<=n; i++){
     fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
  }
  printf("\n\n");

  printf("This is the Copy of the Transposed Graph:\n");
  Graph B = copyGraph(T);
  DFS(B, S);
  printGraph(stdout, B);
  printf("Order: %d\nSize: %d\n", getOrder(B), getSize(B));
  printf("\n");
  fprintf(stdout, "x:  d  f  p\n");
  for(i=1; i<=n; i++){
     fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(B, i), getFinish(B, i), getParent(B, i));
  }
  printf("\n\n");

  printf("This is the Tranpose of the Transposed Graph:\n");
  Graph C = transpose(T);
  DFS(C, S);
  printGraph(stdout, C);
  printf("Order: %d\nSize: %d\n", getOrder(C), getSize(C));
  printf("\n");
  fprintf(stdout, "x:  d  f  p\n");
  for(i=1; i<=n; i++){
     fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(C, i), getFinish(C, i), getParent(C, i));
  }
  printf("\n\n");

  freeGraph(&G);
  freeGraph(&T);
  freeGraph(&C);
  freeGraph(&B);
  freeList(&S);
  return 0;
}
