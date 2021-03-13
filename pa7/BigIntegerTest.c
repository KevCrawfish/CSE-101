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


    A = stringToBigInteger("7402779357");
    B = stringToBigInteger("7402779357");
    C = newBigInteger();
    D = stringToBigInteger("1688014119531601");

    // pos * pos = pos
    multiply(C, A, B);
    if(sign(C) != 1) return 0;
    if(!equals(C, D)) return 0;

    // pos * neg = neg
    negate(B);
    negate(D);
    multiply(C, A, B);
    if(sign(C) != -1) return 0;
    if(!equals(C, D)) return 0;

    makeZero(B);
    multiply(C, A, B);
    if(sign(C) != 0) return 0;



  //////////////////////
  printf("ok\n");
  return 0;
}
