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
  insert(A, "a", 1);
  insert(A, "b", 2);
  delete(A, "a");
  if (size(A) != 2) return 0;
  insert(A, "e", 5);
  delete(A, "c");
  if (size(A) != 2) return 0;
  return 0;
}
