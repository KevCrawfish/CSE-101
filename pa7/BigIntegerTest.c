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
   * Adding numbers fall into one of 4 cases, denote pos = positive number, neg = negative number
   *
   * pos + pos = pos
   *
   * pos + neg = 0
   *           < 0
   *           > 0
   *
   * neg + pos = 0
   *           < 0
   *           > 0
   *
   * neg + neg = neg
   *
   * */
  A = stringToBigInteger("+111122223333");
  B = stringToBigInteger("+222211110000");
  C = newBigInteger();

  //pos + pos = pos
  D = stringToBigInteger("+333333333333");
  add(C, A, B);

  if(!equals(C, D)) return 0;
  freeBigInteger(&B);
  freeBigInteger(&D);

  //add a positive and a negative integer
  //-> pos + neg = 0
  B = stringToBigInteger("-111122223333");
  add(C, A, B);
  if(sign(C) != 0) return 0;
  freeBigInteger(&B);

  //-> pos + neg > 0
  B = stringToBigInteger("-110122223333");
  D = stringToBigInteger("1000000000");
  add(C, A, B);
  if(sign(C) != 1) return 0;
  if(!equals(C, D)) return 0;
  freeBigInteger(&B);
  freeBigInteger(&D);

  //-> pos + neg < 0
  B = stringToBigInteger("-112122223333");
  D = stringToBigInteger("-1000000000");
  add(C, A, B);
  if(sign(C) != -1) return 0;
  if(!equals(C, D)) return 0;
  freeBigInteger(&D);


  //-> neg + neg = neg
  freeBigInteger(&A);
  A = stringToBigInteger("-221211110000");
  D = stringToBigInteger("-333333333333");
  add(C, A, B);
  if(!equals(C, D)) return 0;

  //////////////////////
  printf("ok\n");
  return 0;
}
