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
  A.insertAfter(3);
  A.insertAfter(1);
  A.insertAfter(2);
  A.insertAfter(1);
  A.cleanup();
  if (A.size() != 3) return 0;
  cout << "ok ";
  return 0;
}
