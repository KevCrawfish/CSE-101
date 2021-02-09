//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa4
// Shuffle.cpp
// Uses the list ADT to perform shuffling operations
// Determines how many shuffles are necessary to bring a List back to
//  its original order.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include<fstream>
#include"List.h"

using namespace std;

int counter = 0;

void shuffle(List& D, List &E, int x);

int main(int argc, char *argv[]){
  List A;
  if(argc != 2){
    cout << "Usage: " << argv[0] << " # > outfile" << endl;
    exit(1);
  }

  int num = atoi(argv[1]);
  printf("deck size       shuffle count\n");
  printf("------------------------------\n");
  for(int i = 1; i <= num; i++){
    for(int j = 1; j <= i; j++){
      A.insertBefore(j);
    }
    shuffle(A, A, i);
    printf(" %-15d %d\n", i, counter);
    counter = 0;
    A.clear();
  }
  return 0;
}

void shuffle(List& D, List &E, int x){
  if(x == 1){
    counter++;
    return;
  }

  D.moveFront();
  List B;
  int split = x/2;
  for(int i = 1; i <= split; i++){
    B.insertBefore(D.peekNext());
    D.moveNext();
  }
  B.moveFront();

  if(x == 2){
    B.insertAfter(D.peekNext());
  } else{
    for(int i = 1; i <= x; i += 2){
      B.insertAfter(D.peekNext());
      D.moveNext();
      if(D.position() == x){
        break;
      }
      B.moveNext();
      B.moveNext();
    }
  }
  B.moveFront();
  D.moveFront();

  counter++;
  if(!(B == E)){
    shuffle(B, E, x);
  }
}
