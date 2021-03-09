/****************************************************************************************
*  Kevin M Crawford, kemcrawf, pa7
*  List.h
*  Contains function headers for List.c
*****************************************************************************************/
 #ifndef __LIST_H__
 #define __LIST_H__

#define LIST_ELEMENT long

typedef struct ListObj *List;

// Creates and returns a new empty List.
List newList(void);

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL);

// Returns the number of elements in L.
LIST_ELEMENT length(List L);

// Returns index of cursor element if defined, -1 otherwise.
LIST_ELEMENT index(List L);

// Returns front element of L. Pre: length()>0
LIST_ELEMENT front(List L);

// Returns back element of L. Pre: length()>0
LIST_ELEMENT back(List L);

// Returns cursor element of L. Pre: length()>0, index()>=0
LIST_ELEMENT get(List L);

// Resets L to its original empty state.
void clear(List L);

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, LIST_ELEMENT x);

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
void prepend(List L, LIST_ELEMENT x);

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, LIST_ELEMENT x);

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, LIST_ELEMENT x);

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, LIST_ELEMENT x);

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
