//-----------------------------------------------------------------------------
//  Kevin M Crawford, kemcrawf, pa7
//  Arithmetic.c
//  Top level client for BigInteger ADT
//  Performs artihmetic on arbitrarily large signed integers.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

#define MAX_LEN 10001

int main(int argc, char* argv[]){
  FILE *in, *out;
  BigInteger A = newBigInteger();
  BigInteger B = newBigInteger();
  BigInteger C = newBigInteger();
  BigInteger D = newBigInteger();
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
  // save words from file into array
  // append indexes onto linked list
  //
  fgets(line, MAX_LEN, in);
  fgets(line, MAX_LEN, in);
  long last = strlen(line) - 1;
  line[last] = '\0';
  A = stringToBigInteger(line);
  printBigInteger(stdout, A);
  printf("\n\n");

  fgets(line, MAX_LEN, in);
  fgets(line, MAX_LEN, in);
  last = strlen(line) - 1;
  line[last] = '\0';
  B = stringToBigInteger(line);
  printBigInteger(stdout, B);
  printf("\n\n");

  C = sum(A, B);
  printBigInteger(stdout, C);
  printf("\n\n");

  C = diff(A, B);
  printBigInteger(stdout, C);
  printf("\n\n");

  C = diff(A, A);
  printBigInteger(stdout, C);
  printf("\n\n");

  BigInteger T = newBigInteger();
  T = stringToBigInteger("3");
  C = prod(A, T);
  T = stringToBigInteger("2");
  D = prod(B, T);
  C = diff(C, D);
  printBigInteger(stdout, C);
  printf("\n\n");

  C = prod(A, B);
  printBigInteger(stdout, C);
  printf("\n\n");
  //
  ////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////
  // close files and free memory
  //
  fclose(in);
  fclose(out);
  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);
  freeBigInteger(&D);
  //
  ////////////////////////////////////////////////////////


  return 0;
}
