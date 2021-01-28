/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa3
*  GraphTest.c
*  Test client for Graph ADT.
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
  int i, n=8;
  List S = newList();
  Graph G = newGraph(n);

  for(i=1; i<=n; i++) append(S, i);

  addArc(G, 2,1);
  addArc(G, 2,3);
  addArc(G, 4,3);
  addArc(G, 4,8);
  addArc(G, 5,1);
  addArc(G, 5,2);
  addArc(G, 5,6);
  addArc(G, 6,2);
  addArc(G, 6,3);
  addArc(G, 7,3);
  addArc(G, 7,6);
  addArc(G, 7,8);
  addArc(G, 8,3);
  printGraph(stdout, G);

  DFS(G, S);
  fprintf(stdout, "\n");
  fprintf(stdout, "x:  d  f  p\n");
  for(i=1; i<=n; i++){
     fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
  }
  fprintf(stdout, "\n");
  printList(stdout, S);
  fprintf(stdout, "\n");
  return 0;
}
