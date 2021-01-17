/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa1
*  Lex.c
*  Uses Integer List ADT to alphabetize lines in a file.
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 1000
#define strdup(s) strcpy(malloc(strlen(s) + 1), s)

int main(int argc, char* argv[]){

  List A = newList();
  List B = newList();
  int lines;
  FILE *in, *out;
  char line[MAX_LEN];

  // check command line for correct number of arguments
  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }

  // open files for reading and writing
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

  // read each line of input file
  lines = 0;
  while(fgets(line, MAX_LEN, in) != NULL){
    lines++;
  }

  rewind(in);
  char *inputs[MAX_LEN];
  int j = 0;
  while(fgets(line, MAX_LEN, in) != NULL){
    inputs[j] = strdup(line);
    j++;
  }

  for(int i = 0; i < lines; i++){
    append(A, i);
    append(B, i);
  }

  int left = 0;
  moveFront(A);
  moveFront(B);

  for(int i = 0; i < lines; i++){
    while(left < i){
      if(strcmp(inputs[get(A)],inputs[get(B)]) > 0){
        int temp = get(A);
        int temp2 = get(B);

        moveFront(A);
        moveFront(B);
        for(int j = 0; j < left; j++){
          moveNext(A);
          moveNext(B);
        }
        set(A, temp2);
        set(B, temp2);

        moveFront(A);
        moveFront(B);
        for(int j = 0; j < i; j++){
          moveNext(A);
          moveNext(B);
        }
        set(A, temp);
        set(B, temp);

        moveFront(A);
        for(int j = 0; j < left; j++){
          moveNext(A);
        }
      }
      left++;
      moveNext(A);
    }
    left = 0;
    moveFront(A);
    moveNext(B);
  }

  for(int i = 0; i < lines; i++){
    fprintf(out, "%s", inputs[get(A)]);
    moveNext(A);
  }

  for(int i = 0; i < lines; i++){
    free(inputs[i]);
    inputs[i] = NULL;
  }
  // close files;
  fclose(in);
  fclose(out);
  clear(A);
  clear(B);
  freeList(&A);
  freeList(&B);

  return(0);
}
