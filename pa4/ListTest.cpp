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
  A.insertAfter(1);
  A.insertAfter(2);
  A.moveNext();
  A.insertBefore(3);
  A.movePrev();
  return 0;
  A.insertBefore(5);
  A.insertBefore(12);
  if (A.size() != 5) return 0;
  return 0;
}
