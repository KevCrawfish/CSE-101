//-----------------------------------------------------------------------------
//  Kevin M Crawford, kemcrawf, pa7
//  BigIntegerClient.c
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

int main(){
  BigInteger A = NULL;
  BigInteger B = NULL;
  BigInteger C = NULL;
  BigInteger D = NULL;
  //////////////////////

  A = newBigInteger();
  if (sign(A) != 0) return 0;

  B = stringToBigInteger("13378008135");
  C = stringToBigInteger("+13378008135");
  D = stringToBigInteger("-13378008135");
  if (sign(B) != 1) return 0;
  if (sign(C) != 1) return 0;
  if (sign(D) != -1) return 0;

  //////////////////////
  printf("ok ");
  return 0;
}
