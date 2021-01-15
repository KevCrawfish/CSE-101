// Kevin M Crawford, kemcrawf, pa1
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// private NodeObj type
typedef struct NodeObj{
  int data;
  struct NodeObj *next;
} NodeObj;

// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
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
    for(moveFront(*pL); index(*pL) >= 0; moveNext(*pL)){
      deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
  }
}

// Returns the number of elements in L.
int length(List L){
  if (L == NULL){
    printf("List Error: calling length() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
  if (L == NULL){
    printf("List Error: calling index() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->index;
}

// Returns front element of L. Pre: length()>0
int front(List L){
  if (L == NULL){
    printf("List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling front() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->front->data;
};

// Returns back element of L. Pre: length()>0
int back(List L){
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
int get(List L){
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
int equals(List A, List B){
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
  while(eq && N != NULL){
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}

// Resets L to its original empty state.
void clear(List L){

};

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x){

};

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
  if (L == NULL){
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling moveFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  L->cursor->data = L->front->data;
  L->index = 0;
}

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
  if (L == NULL){
    printf("List Error: calling moveFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling moveFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  L->cursor->data = L->back->data;
  L->index = (L->length - 1);
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){

};

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){

};

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x){

};

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x){
  Node N = newNode(x);

  if(L == NULL){
    printf("List Error: calling append() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    L->front = L->back = N;
  } else{
    L->back->next = N;
    L->back = N;
  }
  L->length++;
};

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){

};

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
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
  L->cursor->next = N;
  L->cursor = N;
  L->length++;
};

// Delete the front element. Pre: length()>0
void deleteFront(List L){
  Node N = NULL;

  if(L == NULL){
    printf("List Error: calling append() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(L) <= 0){
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  N = L->front;
  L->front = L->front->next;
  L->length--;
  freeNode(&N);
};

// Delete the back element. Pre: length()>0
void deleteBack(List L){

};

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){

};

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){

};

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
  return 0;
};
