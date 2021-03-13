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

    A = stringToBigInteger("7402779357");
    B = stringToBigInteger("-4119531601");
    C = newBigInteger();
    D = stringToBigInteger("601");

    multiply(C, A, B);
    if(sign(C) != -1) return 0;

    negate(B);
    multiply(C, A, B);
    if(sign(C) != 1) return 0;

    makeZero(A);
    multiply(C, A, B);
    if(sign(C) != 0) return 0;

    freeBigInteger(&A);
    A = stringToBigInteger("5000000");
    freeBigInteger(&B);
    B = stringToBigInteger("3005000000");
    freeBigInteger(&C);
    C = prod(A, D);
    if(!equals(C, B)) return 0;
    if(compare(A, B) != 1) return 0;
    if(compare(B, A) != -1) return 0;
    freeBigInteger(&D);
    D = copy(C);
    if(!equals(D, C)) return 0;

    add(C, A, B);
    add(C, A, B);
    freeBigInteger(&C);
    C = sum(A, B);
    subtract(C, A, B);
    subtract(C, A, B);
    freeBigInteger(&C);
    C = diff(A, B);

    printf("ok\n");

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);

    return 0;
}
