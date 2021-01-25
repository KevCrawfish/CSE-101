/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa2
*  GraphTest.c
*  Test client for Graph ADT.
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
  Graph G = newGraph(1);

  for(int i = 0; i < 50; i++){
    addArc(G, 50, 1);
  }

  printGraph(stdout, G);

  freeGraph(&G);

  return 0;
}
