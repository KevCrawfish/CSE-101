/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa7
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
  List A = newList();
  append(A, 5);
  append(A, 15);
  append(A, 20);
  if (length(A) != 3) return 0;
  prepend(A, 20);
  prepend(A, 15);
  prepend(A, 5);
  moveBack(A);
  if (index(A) != 5) return 0;
  List B = copyList(A);
  moveFront(B);
  if (get(B) != 5) return 0;
  if (!equal(A, B)) return 0;
  moveFront(B);
  insertAfter(B, 5);
  moveNext(B);
  insertAfter(B, 6);
  moveNext(B);
  insertBefore(B, 7);
  deleteFront(B);
  deleteBack(B);
  moveFront(B);
  moveNext(B);
  if(get(B) != 7 && front(B) != 5 && back(B) != 15) return 0;
  for(int i = 0; i < 500; i++){
    insertAfter(B, 6);
  }
  freeList(&B);
  freeList(&A);

//////////////////////
printf("ok\n");
return 0;
}
