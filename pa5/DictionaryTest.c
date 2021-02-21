//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa5
// DictionaryTest.c
// Test client for Dictionary ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){
  Dictionary A = newDictionary(1);
  insert(A, "c", 3);
  insert(A, "b", 2);
  insert(A, "a", 1);
  beginForward(A);
  makeEmpty(A);
  if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF || size(A) != 0) return 0;
  freeDictionary(&A);
  return 0;
}
