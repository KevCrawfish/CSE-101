/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa2
*  FindPath.c
*  Produces an adjacency list representation of a graph.
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){

  FILE *in, *out;
  int vertices, i = 0;
  int edges[5000];

  ////////////////////////////////////////////////////////
  // check command line for correct number of arguments
  //
  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // open files for reading and writing
  //
  in = fopen(argv[1], "r");
  if(in == NULL){
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  out = fopen(argv[2], "w");
  if(out == NULL){
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // scan first line of input file for # of vertices
  // make new graph with # of vertices
  // read input file for edges util zero
  // save edges into array
  //
  fscanf(in, "%d", &vertices);
  Graph G = newGraph(vertices);

  while(1){
    fscanf(in, "%d", &edges[i]);
    if(edges[i] == 0){
      i++;
      fscanf(in, "%d", &edges[i]);
      break;
    } else {
      i++;
    }
  }
  //
  ////////////////////////////////////////////////////////


  ////////////////////////////////////////////////////////
  // read second part of input file for paths until zero
  // save into array
  //
  while(1){
    fscanf(in, "%d", &edges[i]);
    if(edges[i] == 0){
      break;
    } else {
      i++;
    }
  }
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // add all edges from first part of array to graph
  // print adjaceny list of graph to outfile
  //
  i = 0;
  while(1){
    if(edges[i] == 0){
      break;
    }
    addEdge(G, edges[i], edges[i + 1]);
    i += 2;
  }
  i++;

  printGraph(out, G);
  fprintf(out, "\n");
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // find distance and shortest path from second part of array
  // do a BFS to calculate the distance and path from source
  //
  while(1){
    if(edges[i] == 0){
      break;
    }
    fprintf(out, "The distance from %d to %d is ", edges[i], edges[i + 1]);
    BFS(G, edges[i]);
    if(getDist(G, edges[i + 1]) == INF){
      fprintf(out, "infinity\n");
      fprintf(out, "No %d-%d path exists\n\n", edges[i], edges[i + 1]);
    } else {
      fprintf(out, "%d\n", getDist(G, edges[i + 1]));
      fprintf(out, "A shortest %d-%d path is: ", edges[i], edges[i + 1]);
      List L = newList();
      getPath(L, G, edges[i + 1]);
      printList(out, L);
      fprintf(out, "\n\n");
      freeList(&L);
    }
    i += 2;
  }
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // close files and free any heap memory
  //
  fclose(in);
  fclose(out);
  freeGraph(&G);
  //
  ////////////////////////////////////////////////////////

  return 0;
}
