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
  List B;
  A.insertBefore(1);
  A.insertBefore(2);
  A.insertBefore(2);
  A.insertBefore(1);
  A.insertBefore(2);
  A.insertBefore(3);
  A.insertBefore(1);
  A.findPrev(3);
  A.cleanup();
  if (A.position() != 2) return 0;

  B.insertBefore(1);
  B.insertBefore(2);
  B.insertBefore(2);
  B.insertBefore(1);
  B.insertBefore(2);
  B.insertBefore(3);
  B.insertBefore(1);
  B.findPrev(3);
  B.movePrev();
  B.cleanup();
  if (B.position() != 2) return 0;
  cout << "ok ";
  return 0;
}
