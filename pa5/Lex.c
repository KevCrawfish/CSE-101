//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa5
// Lex.c
// Uses the Dictionary ADT to alphabetize lines in a file
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 1000
#define strdup(s) strcpy(malloc(strlen(s) + 1), s)

int main(int argc, char* argv[]){

  Dictionary A = newDictionary(0);
  int lines;
  FILE *in, *out;
  char line[MAX_LEN];

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
  // read each line of input file
  // save words from file into tree
  //
  lines = 0;
  while(fgets(line, MAX_LEN, in) != NULL){
    insert(A, strdup(line), lines);
    lines++;
  }
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // Print ordered tree
  //
  for(beginForward(A); currentVal(A)!=VAL_UNDEF; next(A)){
     fprintf(out, "%s", currentKey(A));
  }
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // close files and free memory
  //
  fclose(in);
  fclose(out);
  freeDictionary(&A);
  //
  ////////////////////////////////////////////////////////


}
