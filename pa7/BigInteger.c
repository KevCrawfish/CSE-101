//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa7
// BigInteger.c
// BigInteger implementation file
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"BigInteger.h"

// Exported type  -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj{
  List mag;
  int sign;
} BigIntegerObj;


// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
  BigInteger B = malloc(sizeof(BigIntegerObj));
  B->mag = newList();
  B->sign = 0;
  return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){

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
  return 0;
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

  if (s[0] == '-'){
    B->sign = -1;
  } else {
    B->sign = 1;
  }

  if(s[0] == '-' || s[0] == '+'){
    tmp = 1;
  }

  for(long i = 0; i < strlen(s); i += 2){
    if(tmp == 1){
      i++;
      tmp = 0;
    }
    if((i + 2) > strlen(s)){
      append(B->mag, strtol(strncpy(malloc(1), &s[i], 1), &ptr, 10));
      break;
    }
    append(B->mag, strtol(strncpy(malloc(2), &s[i], 2), &ptr, 10));
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

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state:  S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){

}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
  return 0;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state:  D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){

}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B){
  return 0;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state:  P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){

}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
  return 0;
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

}
