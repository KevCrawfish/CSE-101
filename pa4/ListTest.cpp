//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa4
// ListTest.cpp
// A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

int main(){
  List A;
  A.insertAfter(77);
  A.insertAfter(55);
  A.insertAfter(1);
  A.insertAfter(34);
  A.insertAfter(1);
  A.insertAfter(77);
  A.insertAfter(77);
  A.insertAfter(34);
  if (A.findNext(99) != -1) return 0;
  if (A.position() != A.size()) return 0;

  A.moveFront();
  if (A.findNext(1) != 4) return 0;
  if (A.findNext(1) != 6) return 0;
  if (A.findNext(1) != -1) return 0;

  A.moveFront();
  A.cleanup();
  if (A.findNext(1) != 3) return 6;
  if (A.findNext(1) != -1) return 7;
  return 0;
}
