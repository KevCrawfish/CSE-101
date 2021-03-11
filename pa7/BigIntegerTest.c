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

  A = stringToBigInteger("+111122223333");
  B = stringToBigInteger("+222211110000");

  //pos + pos = pos
  D = stringToBigInteger("+333333333333");
  C = sum(A, B);

  if(!equals(C, D)) return 0;
  freeBigInteger(&B);
  freeBigInteger(&C);
  freeBigInteger(&D);

  //-> neg + pos == 0
  negate(A); //A-> -111122223333
  B = stringToBigInteger("+111122223333");
  C = sum(A, B);
  if(sign(C) != 0) return 0;
  freeBigInteger(&B);
  freeBigInteger(&C);

  //-> neg + pos > 0
  B = stringToBigInteger("+112122223333");
  D = stringToBigInteger("1000000000");
  C = sum(A, B);
  if(sign(C) != 1) return 0;
  if(!equals(C, D)) return 0;
  freeBigInteger(&B);
  freeBigInteger(&C);
  freeBigInteger(&D);

  //-> neg + pos < 0
  //negate(*pA);
  B = stringToBigInteger("+110122223333");
  D = stringToBigInteger("-1000000000");
  C = sum(A, B);
  if(sign(C) != -1) return 0;
  if(!equals(C, D)) return 0;
  freeBigInteger(&D);

  //-> neg + neg
  freeBigInteger(&B);
  freeBigInteger(&C);
  B = stringToBigInteger("-222211110000");
  D = stringToBigInteger("-333333333333");
  C = sum(A, B);
  if(!equals(C, D)) return 0;

  //////////////////////
  printf("ok\n");
  return 0;
}
