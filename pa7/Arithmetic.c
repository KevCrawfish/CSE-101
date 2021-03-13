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
  BigInteger E = newBigInteger();
  BigInteger F = newBigInteger();
  BigInteger G = newBigInteger();
  BigInteger H = newBigInteger();
  BigInteger T = newBigInteger();
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
  // save string to bigint and do maths stuff
  //
  fgets(line, MAX_LEN, in);
  fgets(line, MAX_LEN, in);
  long last = strlen(line) - 1;
  line[last] = '\0';
  freeBigInteger(&A);
  A = stringToBigInteger(line);
  printBigInteger(out, A);
  fprintf(out, "\n\n");
  freeBigInteger(&E);
  E = copy(A);

  fgets(line, MAX_LEN, in);
  fgets(line, MAX_LEN, in);
  last = strlen(line) - 1;
  line[last] = '\0';
  freeBigInteger(&B);
  B = stringToBigInteger(line);
  printBigInteger(out, B);
  fprintf(out, "\n\n");
  freeBigInteger(&F);
  F = copy(B);

  freeBigInteger(&C);
  C = sum(A, B);
  printBigInteger(out, C);
  fprintf(out, "\n\n");

  freeBigInteger(&C);
  C = diff(A, B);
  printBigInteger(out, C);
  fprintf(out, "\n\n"); 

  freeBigInteger(&C);
  C = diff(A, E);
  printBigInteger(out, C);
  fprintf(out, "\n\n");

  freeBigInteger(&T);
  T = stringToBigInteger("3");
  multiply(C, A, T);
  freeBigInteger(&T);
  T = stringToBigInteger("2");
  multiply(G, B, T);
  freeBigInteger(&H);
  H = diff(C, G);
  printBigInteger(out, H);
  fprintf(out, "\n\n");

  freeBigInteger(&C);
  C = prod(A, B);
  printBigInteger(out, C);
  fprintf(out, "\n\n");

  freeBigInteger(&C);
  C = prod(A, E);
  printBigInteger(out, C);
  fprintf(out, "\n\n");

  freeBigInteger(&C);
  C = prod(B, F);
  printBigInteger(out, C);
  fprintf(out, "\n\n");

  multiply(C, A, E);
  multiply(G, C, E);
  multiply(C, G, E);
  freeBigInteger(&T);
  T = stringToBigInteger("9");
  multiply(G, C, T);
  //
  multiply(C, B, F);
  multiply(H, C, F);
  multiply(C, H, F);
  multiply(H, C, F);
  freeBigInteger(&T);
  T = stringToBigInteger("16");
  multiply(C, H, T);
  //
  add(H, C, G);
  printBigInteger(out, H);
  fprintf(out, "\n\n");
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
  freeBigInteger(&E);
  freeBigInteger(&F);
  freeBigInteger(&G);
  freeBigInteger(&H);
  freeBigInteger(&T);
  //
  ////////////////////////////////////////////////////////


  return 0;
}
