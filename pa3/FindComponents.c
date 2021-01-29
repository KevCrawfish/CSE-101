/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa3
*  FindComponents.c
*  Produces an adjacency list and finds strongly connected components of a digraph.
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
  // add all edges from first part of array to graph
  // print adjaceny list of graph to outfile
  //
  i = 0;
  while(1){
    if(edges[i] == 0){
      break;
    }
    addArc(G, edges[i], edges[i + 1]);
    i += 2;
  }
  i++;
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\n");
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // find strongly connected components
  //
  List L = newList();
  for(i=1; i<=vertices; i++) append(L, i);
  DFS(G, L);
  Graph T = transpose(G);
  DFS(T, L);

  i = 0;
  for(moveBack(L); index(L)>=0; movePrev(L)){
    if(getParent(T, get(L)) == 0){
      i++;
    }
  }
  int cmp = i;
  fprintf(out, "G contains %d strongly connected components:\n", i);

  i = 1;
  for(moveBack(L); index(L)>=0; movePrev(L)){
    if(getParent(T, get(L)) == 0){
      fprintf(out, "Component %d: ", i);
      fprintf(out, "%d ", get(L));
      moveNext(L);
      if(index(L) < 0){
        moveBack(L);
        fprintf(out, "\n");
        i++;
        continue;
      }
      while(getParent(T, get(L)) != 0){
        fprintf(out, "%d ", get(L));
        moveNext(L);
        if(index(L) < 0){
          moveBack(L);
          break;
        }
      }
      movePrev(L);
      while(getParent(T, get(L)) != 0){
        movePrev(L);
        if(index(L) < 0){
          break;
        }
      }
      fprintf(out, "\n");
      if(i == cmp){
        break;
      }
      i++;
    }
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
