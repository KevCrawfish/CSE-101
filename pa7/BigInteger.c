//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa7
// BigInteger.c
// BigInteger implementation file
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"BigInteger.h"

// Exported type  -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj{
  List mag;
  int sign;
  int size;
} BigIntegerObj;


// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
  BigInteger B = malloc(sizeof(BigIntegerObj));
  B->mag = newList();
  B->sign = 0;
  B->size = 0;
  return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
  freeList(&(*pN)->mag);
  free(*pN);
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
  return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
  moveFront(A->mag);
  moveFront(B->mag);

  if(equals(A, B)){
    return 0;
  }
  if(get(A->mag) < get(B->mag)){
    return -1;
  } else {
    return 1;
  }
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
  if(A->sign != B->sign){
    return 0;
  }

  if(equal(A->mag, B->mag)){
    return 1;
  }

  return 0;
}

int NumLen(BigInteger N){
  if (get(N->mag) >= 1000000000)  return 10;
  if (get(N->mag) >= 100000000)  return 9;
  if (get(N->mag) >= 10000000)   return 8;
  if (get(N->mag) >= 1000000)    return 7;
  if (get(N->mag) >= 100000)     return 6;
  if (get(N->mag) >= 10000)      return 5;
  if (get(N->mag) >= 1000)       return 4;
  if (get(N->mag) >= 100)        return 3;
  if (get(N->mag) >= 10)         return 2;
  return 1;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
  freeList(&N->mag);
  N->mag = newList();
  N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
  if (N->sign == -1){
    N->sign = 1;
  } else if(N->sign == 1){
    N->sign = -1;
  }
}


// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
  int tmp;
  char *ptr;
  BigInteger B = newBigInteger();

  // Read sign of number
  if (s[0] == '-'){
    B->sign = -1;
  } else {
    B->sign = 1;
  }

  if(s[0] == '-' || s[0] == '+'){
    tmp = 1;
  }

  B->size = strlen(s);

  // Read in 9 numbers at a time
  for(long i = 0; i < strlen(s); i += 9){
    if(tmp == 1){
      i++;
      tmp = 0;
    }
    if((i + 9) > strlen(s)){
      append(B->mag, strtol(strncpy(malloc(9), &s[i], 9), &ptr, 10));
      break;
    }
    append(B->mag, strtol(strncpy(malloc(9), &s[i], 9), &ptr, 10));
  }

  return B;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
  BigInteger B = newBigInteger();
  B->mag = copyList(N->mag);
  B->sign = N->sign;
  return B;
}

void normaliseadd(BigInteger S){
  if(get(S->mag) < 0){
    set(S->mag, (get(S->mag) * - 1));
    S->sign = -1;
  }
  if(get(S->mag) == 0){
    S->sign = 0;
  }
  return;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state:  S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
  int j = 0;
  int i = 0;
  makeZero(S);
  moveFront(A->mag);
  moveFront(B->mag);

  if(A->sign == -1 && B->sign == -1){
    while(index(A->mag)>=0){
      append(S->mag, (get(A->mag) + get(B->mag)));
      moveNext(A->mag);
      moveNext(B->mag);
    }

    S->sign = -1;
    return;
  }

  if(A->sign == -1){
    while(index(A->mag)>=0){
      append(S->mag, (get(B->mag) - get(A->mag)));
      if(j != 0){
        if((index(A->mag) + 1) == length(A->mag)){
          i += NumLen(A) - 1;
        } else {
          i += 8;
        }
      }
      moveNext(A->mag);
      moveNext(B->mag);
      j++;
    }
    j = 1;
    for(int z = 0; z < i; z++){
      j *= 10;
    }
    moveFront(S->mag);
    set(S->mag, (get(S->mag) * j));
    if(get(S->mag) != 0){
      S->sign = 1;
    }
    normaliseadd(S);
    return;
  }

  if(B->sign == -1){
    while(index(A->mag)>=0){
      append(S->mag, (get(A->mag) - get(B->mag)));
      if(j != 0){
        if((index(A->mag) + 1) == length(A->mag)){
          i += NumLen(A) - 1;
        } else {
          i += 8;
        }
      }
      moveNext(A->mag);
      moveNext(B->mag);
      j++;
    }
    j = 1;
    for(int z = 0; z < i; z++){
      j *= 10;
    }
    moveFront(S->mag);
    set(S->mag, (get(S->mag) * j));
    if(get(S->mag) != 0){
      S->sign = 1;
    }
    normaliseadd(S);
    return;
  }

  while(index(A->mag)>=0){
    append(S->mag, (get(A->mag) + get(B->mag)));
    moveNext(A->mag);
    moveNext(B->mag);
  }

  S->sign = 1;
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
  BigInteger S = newBigInteger();
  add(S, A, B);
  return S;
}

void normalisesub(BigInteger D){
  if(get(D->mag) == 0){
    D->sign = 0;
  }
  if(NumLen(D) > 9){
    set(D->mag, (get(D->mag) / 10));
  }
  return;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state:  D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
  makeZero(D);
  moveFront(A->mag);
  moveFront(B->mag);

  if(B->sign == -1 && A->sign == -1){
    A->sign = 1;
    add(D, A, B);
    A->sign = -1;
    moveFront(A->mag);
    moveFront(B->mag);
    if(get(A->mag) == get(B->mag)){
      D->sign = 0;
    } else if(get(A->mag) > get(B->mag)){
      D->sign = -1;
    } else {
      D->sign = 1;
    }
    return;
  }

  if(B->sign == 1 && A->sign == -1){
    A->sign = 1;
    add(D, A, B);
    A->sign = -1;
    D->sign = -1;
    return;
  }

  if(A->sign == 1 && B->sign == -1){
    B->sign = 1;
    add(D, A, B);
    B->sign = -1;
    return;
  }

  if(A->sign == 1 && B->sign == 1){
    if(get(B->mag) > get(A->mag)){
      A->sign = -1;
      add(D, A, B);
      A->sign = 1;
      D->sign = -1;
    } else {
      B->sign = -1;
      add(D, A, B);
      B->sign = 1;
    }
  }
  normalisesub(D);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
  BigInteger D = newBigInteger();
  subtract(D, A, B);
  return D;
}

void mulnormalise(BigInteger P){
  long c = 0;
  moveBack(P->mag);
  while(index(P->mag)>=0){
    set(P->mag, (get(P->mag) + c));
    c = 0;
    if(get(P->mag) >= 1000000000){
      c = get(P->mag) / 1000000000;
      set(P->mag, (get(P->mag) % 1000000000));
    }
    movePrev(P->mag);
  }
  if(c > 0){
    moveFront(P->mag);
    insertBefore(P->mag, c);
  }
}

void muladd(BigInteger T, BigInteger P){
  while(length(P->mag) != length(T->mag)){
    prepend(P->mag, 0);
  }

  moveBack(P->mag);
  moveBack(T->mag);

  while(index(T->mag)>=0){
    set(P->mag, get(T->mag) + get(P->mag));
    movePrev(P->mag);
    movePrev(T->mag);
  }
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state:  P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
  
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
  BigInteger S = newBigInteger();
  return S;
}


/* These 3 functions are not required *****************************************

// divide()
// Places the quotient and remainder of A upon division by B in the existing
// BigIntegers Q and R respectively, overwriting their current states:
// A = B*Q + R
void divide(BigInteger Q, BigInteger R, BigInteger A, BigInteger B);

// quot()
// Returns a reference to a new BigInteger object representing the quotient
// of A upon division by B.
BigInteger quot(BigInteger A, BigInteger B);

// rem()
// Returns a reference to a new BigInteger object representing the remainder
// of A upon division by B.
BigInteger rem(BigInteger A, BigInteger B);

******************************************************************************/


// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
  if(N->sign == -1){
    printf("-");
  }
  int i = 0;
  for(moveFront(N->mag); index(N->mag)>=0; moveNext(N->mag)){
    if(NumLen(N) < 9){
      if((index(N->mag) + 1) == length(N->mag)){
        for(int j = 0; j < ((N->size - i) - NumLen(N)); j++){
          printf("0");
        }
      } else {
        for(int j = 0; j < (9 - NumLen(N)); j++){
          printf("0");
        }
      }
    }
    fprintf(out, "%ld ", get(N->mag));
    i += 10;
  }
}
