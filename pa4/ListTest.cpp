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
  A.insertBefore(5);
  A.insertBefore(10);
  A.insertBefore(15);
  A.insertBefore(176);
  A.insertBefore(200);
  A.findPrev(15);
  A.eraseBefore();
  if (A.position() != 1) return 1;

  A.insertAfter(175);
  A.eraseBefore();
  if (A.position() != 0) return 2;

  A.insertBefore(15);
  A.insertBefore(50);
  if (A.position() != 2) return 3;

  A.findNext(15);
  A.eraseBefore();
  if (A.position() != 3) return 4;

  A.findPrev(15);
  if (A.position() != 0) return 5;

  A.moveBack();
  if (A.position() != 5) return 6;
  A.eraseBefore();
  A.eraseBefore();
  A.eraseBefore();
  A.eraseBefore();
  A.eraseBefore();
  if (A.position() != 0) return 7;
  return 0;
}
