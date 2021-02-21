//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa5
// Dictionary.c
// Implementation file for Dictionary ADT.
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

// Exported type --------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
  KEY_TYPE key;
  VAL_TYPE val;
  struct NodeObj *left;
  struct NodeObj *right;
  struct NodeObj *parent;
} NodeObj;

// private Node type
typedef NodeObj *Node;

typedef struct DictionaryObj{
  Node root;
  Node nil;
  Node cursor;
  Node look;
  int uniq;
  int size;
} DictionaryObj;

// Constructors-Destructors ---------------------------------------------------

// Returns reference to new Node object. Initializes next and data fields.
Node newNode(KEY_TYPE k, VAL_TYPE v){
  Node N = malloc(sizeof(NodeObj));
  N->key = k;
  N->val = v;
  N->left = NULL;
  N->right = NULL;
  N->parent = NULL;
  return N;
}

// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN){
  if(pN != NULL && *pN != NULL){
    free(*pN);
    *pN = NULL;
  }
}

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary
// will accept duplicate keys, i.e. distinct pairs with identical keys. If
// unique==true (1 or any non-zero value), then duplicate keys will not be
// accepted. In this case, the operation insert(D, k) will enforce the
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
  Dictionary D = malloc(sizeof(DictionaryObj));
  Node NIL = newNode(KEY_UNDEF, VAL_UNDEF);
  D->nil = NIL;
  D->root = D->nil;
  D->root->left = D->nil;
  D->root->right = D->nil;
  D->root->parent = D->nil;
  D->cursor = D->root;
  D->look = D->root;
  D->uniq = unique;
  D->size = 0;
  return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
  if(pD != NULL && *pD != NULL){
    makeEmpty(*pD);
    free((*pD)->nil);
    free(*pD);
    pD = NULL;
  }
}


// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
  return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
  return D->uniq;
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
  if(D->look == D->nil || KEY_CMP(D->look->key, k) == 0){
    return D->look->val;
  } else if (KEY_CMP(k, D->look->key) < 0){
    D->look = D->look->left;
    return lookup(D, k);
  } else { // k > D->cursor->key
    D->look = D->look->right;
    return lookup(D, k);
  }
}


// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D.
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced.
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
  if(getUnique(D)){
    D->look = D->root;
    if(lookup(D, k) != VAL_UNDEF){
      return;
    }
  }

  Node z = newNode(k, v);
  Node y = D->nil;
  Node x = D->root;
  while(x != D->nil){
    y = x;
    if(KEY_CMP(z->key, x->key) < 0){
      x = x->left;
    } else {
      x = x->right;
    }
  }
  z->parent = y;
  z->left = D->nil;
  z->right = D->nil;
  if(y == D->nil){
    D->root = z;
  } else if (KEY_CMP(z->key, y->key) < 0){
    y->left = z;
  } else {
    y->right = z;
  }
  D->size++;
  D->look = D->root;
}

// Helper function for delete
void Transplant(Dictionary D, Node u, Node v){
  if(u->parent == D->nil){
    D->root = v;
  } else if (u == u->parent->left){
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if(v != D->nil){
    v->parent = u->parent;
  }
}

// Finds the leftmost node of the tree.
Node TreeMin(Dictionary D, Node z){
  Node x = z;
  while(x->left != D->nil){
    x = x->left;
  }
  return x;
}

// Finds the rightmost node of the tree.
Node TreeMax(Dictionary D, Node z){
  Node x = z;
  while(x->right != D->nil){
    x = x->right;
  }
  return x;
}

// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
  if(D->cursor == D->nil || KEY_CMP(D->cursor->key, k) == 0){
    D->cursor = D->nil;
  }
  D->look = D->root;
  if(lookup(D, k) == VAL_UNDEF){
    return;
  }
  Node z = D->look;

  if(z->left == D->nil){
    Transplant(D, z, z->right);
  } else if (z->right == D->nil){
    Transplant(D, z, z->left);
  } else {
    Node y = TreeMin(D, z->right);
    if(y->parent != z){
      Transplant(D, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    Transplant(D, z, y);
    y->left = z->left;
    y->left->parent = y;
  }
  free(z);
  D->size--;
  D->look = D->root;
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
  while(size(D) != 0){
    beginForward(D);
    delete(D, currentKey(D));
  }
}

// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginForward(Dictionary D){
  Node x = D->root;
  while(x->left != D->nil){
    x = x->left;
  }
  D->cursor = x;
  return x->val;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
  Node x = D->root;
  while(x->right != D->nil){
    x = x->right;
  }
  D->cursor = x;
  return x->val;
}

// currentKey()
// If an iteration (forward or reverse) over D has started, returns the
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
  return D->cursor->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the
// value corresponding to the current key. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
  return D->cursor->val;
}

// next()
// If an iteration (forward or reverse) over D has started, and has not
// reached the last pair, moves to the next key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the last pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE next(Dictionary D){
  Node x = D->cursor;
  if(x->right != D->nil){
    D->cursor = TreeMin(D, x->right);
    return D->cursor->val;
  }
  Node y = x->parent;
  while(y != D->nil && x == y->right){
    x = y;
    y = y->parent;
  }
  D->cursor = y;
  return D->cursor->val;
}


// prev()
// If an iteration (forward or reverse) over D has started, and has not
// reached the first pair, moves to the previous key in D (as defined by the
// order operator KEY_CMP()), and returns the value corresponding to the
// new key. If an iteration has started, and has reached the first pair,
// ends the iteration and returns VAL_UNDEF. If no iteration is underway,
// returns VAL_UNDEF.
VAL_TYPE prev(Dictionary D){
  Node x = D->cursor;
  if(x->left != D->nil){
    D->cursor = TreeMax(D, x->left);
    return D->cursor->val;
  }
  Node y = x->parent;
  while(y != D->nil && x == y->left){
    x = y;
    y = y->parent;
  }
  D->cursor = y;
  return D->cursor->val;
}


// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
  VAL_TYPE x;
  for(x=beginForward(D); currentVal(D)!=VAL_UNDEF; x=next(D)){
     printf("%s %d\n", currentKey(D), x);
  }
}
