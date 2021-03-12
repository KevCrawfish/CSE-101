/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa7
*  List.c
*  Doubly Linked List ADT implementation.
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 300

// private NodeObj type
typedef struct NodeObj{
  LIST_ELEMENT data;
  struct NodeObj *next;
  struct NodeObj *prev;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  LIST_ELEMENT length;
  LIST_ELEMENT index;
} ListObj;

// Returns reference to new Node object. Initializes next and data fields.
Node newNode(LIST_ELEMENT data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return N;
}

// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN){
  if(pN != NULL && *pN != NULL){
    free(*pN);
    *pN = NULL;
  }
}

// Creates and returns a new empty List.
List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
  L->length = 0;
  L->index = -1;
  return L;
}

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL){
  if(pL != NULL && *pL != NULL){
    while(length(*pL) > 0){
      deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
  }
}

// Returns the number of elements in L.
LIST_ELEMENT length(List L){
  if (L == NULL){
    printf("List Error: calling length() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
LIST_ELEMENT index(List L){
  if (L == NULL){
    printf("List Error: calling index() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->index;
}

// Returns front element of L. Pre: length()>0
LIST_ELEMENT front(List L){
  if (L == NULL){
    printf("List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling front() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->front->data;
}

// Returns back element of L. Pre: length()>0
LIST_ELEMENT back(List L){
  if (L == NULL){
    printf("List Error: calling back() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling back() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
LIST_ELEMENT get(List L){
  if (L == NULL){
    printf("List Error: calling get() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling get() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0){
    printf("List Error: calling get() on an undefined cursor element\n");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
LIST_ELEMENT equal(List A, List B){
  int eq = 0;
  Node N = NULL;
  Node M = NULL;

  if (A == NULL || B == NULL){
    printf("List Error: calling equals() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  eq = (A->length == B->length);
  N = A->front;
  M = B->front;
  while(eq && N != NULL && M != NULL){
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}


// Resets L to its original empty state.
void clear(List L){
  if(L != NULL){
    while(length(L) > 0){
      deleteFront(L);
    }
  }
  L->index = -1;
  L->length = 0;
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, LIST_ELEMENT x){
  if(L == NULL){
    printf("List Error: calling set() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling set() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0){
    printf("List Error: calling set() on an undefined cursor element\n");
    exit(EXIT_FAILURE);
  }
  L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
  if (L == NULL){
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    return;
  }
  L->cursor = L->front;
  L->index = 0;
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
  if (L == NULL){
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling moveBack() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  L->cursor = L->back;
  L->index = (L->length - 1);
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
  if (L == NULL){
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling movePrev() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL){
    return;
  }
  if (L->cursor == L->front){
    L->cursor = NULL;
    L->index = -1;
  } else {
    L->cursor = L->cursor->prev;
    L->index -= 1;
  }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
  if (L == NULL){
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == NULL){
    return;
  }
  if (L->cursor == L->back){
    L->cursor = NULL;
    L->index = -1;
  } else {
    L->cursor = L->cursor->next;
    L->index++;
  }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, LIST_ELEMENT x){
  Node N = newNode(x);

  if(L == NULL){
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    L->front = L->back = N;
  } else{
    N->next = L->front;
    L->front->prev = N;
    L->front = N;
  }
  L->index++;
  L->length++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, LIST_ELEMENT x){
  Node N = newNode(x);

  if(L == NULL){
    printf("List Error: calling append() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    L->front = L->back = N;
  } else{
    L->back->next = N;
    N->prev = L->back;
    L->back = N;
  }
  L->length++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, LIST_ELEMENT x){
  Node N = newNode(x);

  if(L == NULL){
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling insertBefore() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0){
    printf("List Error: calling insertBefore() on an undefined cursor element\n");
    exit(EXIT_FAILURE);
  }
  if(L->cursor == L->front){
    freeNode(&N);
    prepend(L, x);
    return;
  }

  ////////////////////////////////////////////////////////
  // this might be unneccesary
  // but I was getting bugs initially
  // the quickest fix was to set the cursor
  // one step back without using prev
  // then do an insert after
  // and I'm too afraid to change it
  //
  L->cursor = L->front;
  for(int i = 0; i < L->index - 1; i++){
    L->cursor = L->cursor->next;
  }
  N->next = L->cursor->next;
  N->prev = L->cursor;
  L->cursor->next = N;
  L->cursor->next->prev = N;
  L->cursor = N->next;
  L->index++;
  L->length++;
  //
  ////////////////////////////////////////////////////////
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, LIST_ELEMENT x){
  Node N = newNode(x);

  if(L == NULL){
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling insertAfter() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0){
    printf("List Error: calling insertAfter() on an undefined cursor element\n");
    exit(EXIT_FAILURE);
  }

  N->next = L->cursor->next;
  L->cursor->next = N;
  L->cursor->next->prev = N;
  N->prev = L->cursor;
  if(L->cursor->next->next != NULL){
    L->cursor->next->next->prev = N;
  }
  L->length++;
  if(L->cursor == L->back){
    L->back->next->prev = L->back;
    L->back = L->back->next;
  }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L){
  Node N = NULL;

  if(L == NULL){
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  L->index--;
  if(L->cursor == L->front){
    L->cursor = NULL;
    L->index = -1;
  }
  N = L->front;
  if(length(L) > 1){
    L->front = L->front->next;
  } else {
    L->front = NULL;
  }
  L->length--;
  freeNode(&N);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L){
  Node N = NULL;

  if(L == NULL){
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling deleteBack() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if(L->cursor == L->back){
    L->cursor = NULL;
    L->index = -1;
  }
  N = L->back;
  L->back = L->back->prev;
  L->length--;
  if(L->length != 0){
    L->back->next = NULL;
  }
  freeNode(&N);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
  Node N = NULL;

  if(L == NULL){
    printf("List Error: calling delete() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling delete() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if(index(L) < 0){
    printf("List Error: calling delete() on an undefined cursor element\n");
    exit(EXIT_FAILURE);
  }
  if(L->cursor == L->front){
    L->cursor = NULL;
    L->index = -1;
    N = L->front;
    L->front = L->front->next;
    L->length--;
    freeNode(&N);
    return;
  }
  if(L->cursor == L->back){
    L->cursor = NULL;
    L->index = -1;
    N = L->back;
    L->back = L->back->prev;
    L->length--;
    if(L->length != 0){
      L->back->next = NULL;
    }
    freeNode(&N);
    return;
  }

  N = L->cursor;
  L->cursor->prev->next = L->cursor->next;
  L->cursor = NULL;
  L->index = -1;
  L->length--;
  freeNode(&N);
}

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE *out, List L){
  if(L == NULL){
    printf("List Error: calling printList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  for(moveFront(L); index(L)>=0; moveNext(L)){
     fprintf(out, "%ld ", get(L));
  }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
  List R = newList();
  LIST_ELEMENT x;
  LIST_ELEMENT temp = L->index;

  if(L == NULL){
    printf("List Error: calling copyList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  for(moveFront(L); index(L) >= 0; moveNext(L)){
    x = get(L);
    append(R, x);
  }
  L->index = temp;
  moveFront(L);
  for(LIST_ELEMENT i = 0; i < temp; i++){
    moveNext(L);
  }
  return R;
}
