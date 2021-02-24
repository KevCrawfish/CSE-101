//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa6
// DictionaryTest.c
// Test client for Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){
  Dictionary A = newDictionary(1);
  //Dictionary B = newDictionary(0);
  int* pI = calloc(10, sizeof(int));
  for (int i=0; i < 10; i++) pI[i]=i+10;

  if (lookup(A, "f") != VAL_UNDEF) return 0;
  insert(A, "m", &pI[0]);
  insert(A, "n", &pI[1]);
  insert(A, "o", &pI[2]);
  insert(A, "p", &pI[3]);
  insert(A, "q", &pI[4]);
  insert(A, "f", &pI[5]);
  insert(A, "e", &pI[6]);
  if (*lookup(A, "m") != pI[0]) return 0;
  delete(A, "n");
  if (lookup(A, "n") != VAL_UNDEF) return 0;
  if (*lookup(A, "q") != pI[4]) return 0;

  printf("ok\n");
  return 0;
}
