/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa2
*  List.h
*  Contains function headers for List.c
*****************************************************************************************/
 #ifndef __LIST_H__
 #define __LIST_H__

typedef struct ListObj *List;

// Creates and returns a new empty List.
List newList(void);

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL);

// Returns the number of elements in L.
int length(List L);

// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// Returns front element of L. Pre: length()>0
int front(List L);

// Returns back element of L. Pre: length()>0
int back(List L);

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L);

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B);

// Resets L to its original empty state.
void clear(List L);

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x);

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L);

// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L);

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L);

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L);

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x);

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x);

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x);

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x);

// Delete the front element. Pre: length()>0
void deleteFront(List L);

// Delete the back element. Pre: length()>0
void deleteBack(List L);

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L);

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE *out, List L);

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L);

 #endif
