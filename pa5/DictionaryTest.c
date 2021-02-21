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
  Dictionary B = newDictionary(0);
  insert(B, "d", 2);
  insert(B, "d", 5);
  delete(B, "d");
  if (lookup(B, "d") != 5) return 0;
  printf("ok ");
  return 0;
}
