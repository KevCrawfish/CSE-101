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

  /*
   * subtracting numbers fall into one of 4 cases, denote pos = positive number, neg = negative number
   *
   * pos - pos = 0
   *           < 0
   *           > 0
   *
   * pos - neg = pos
   *
   * neg - pos = neg
   *
   * neg - neg = 0
   *           < 0
   *           > 0
   *
   * */

  // pos - pos = 0
  A = stringToBigInteger("+111122223333");
  B = stringToBigInteger("+111122223333");
  C = newBigInteger();

  subtract(C, A, B);
  if(sign(C) != 0) return 0;

  printf("ok\n");
  return 0;

  // pos - pos < 0
  freeBigInteger(&B);
  B = stringToBigInteger("121122223333");
  D = stringToBigInteger("-10000000000");
  subtract(C, A, B);
  if(sign(C) != -1) return 0;
  if(!equals(C, D)) return 0;
  freeBigInteger(&D);

  // pos - pos > 0
  freeBigInteger(B);
  B = stringToBigInteger("101122223333");
  D = stringToBigInteger("10000000000");
  subtract(C, A, B);
  if(sign(C) != 1) return 0;
  if(!equals(C, D)) return 0;
  freeBigInteger(&D);

  //pos - neg = pos
  negate(B);
  D = stringToBigInteger("212244446666");
  subtract(C, A, B);
  if(sign(C) != 1) return 0;
  if(!equals(C, D)) return 0;

  //neg - pos = neg
  negate(D);
  subtract(C, B, A);
  if(sign(C) != -1) return 0;
  if(!equals(C, D)) return 0;


  //////////////////////
  printf("ok\n");
  return 0;
}
