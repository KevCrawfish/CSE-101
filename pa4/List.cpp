//-----------------------------------------------------------------------------
// Kevin M Crawford, kemcrawf, pa4
// List.h
// Implementation file for List ADT. List is a double ended queue with a vertical
// cursor standing between elements. The cursor position is always defined
// to be an int in the range 0 (at front) to length of List (at back).
// An empty list consists of the vertical cursor only, with no elements.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

// Private Constructor --------------------------------------------------------

List::Node::Node(int x){
  data = x;
  next = nullptr;
  prev = nullptr;
}

// Class Constructors & Destructors ----------------------------------------

// Creates new List in the empty state.
List::List(){
  frontDummy = nullptr;
  backDummy = nullptr;
  beforeCursor = nullptr;
  afterCursor = nullptr;
  pos_cursor = 0;
  num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
  // make empty list
  frontDummy = nullptr;
  backDummy = nullptr;
  beforeCursor = nullptr;
  afterCursor = nullptr;
  pos_cursor = 0;
  num_elements = 0;

  // load elements of list into this
  Node *N = L.frontDummy;
  while(N != nullptr){
    this->insertBefore(N->data);
    N = N->next;
  }
  pos_cursor = 0;
  afterCursor = frontDummy;
}

// Destructor
List::~List(){
  clear();
  delete frontDummy;
  delete backDummy;
}


// Access functions --------------------------------------------------------

// isEmpty()
// Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
  return(num_elements == 0);
}

// size()
// Returns the size of this List.
int List::size(){
  return num_elements;
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position(){
  return pos_cursor;
}


// Manipulation procedures -------------------------------------------------

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
  pos_cursor = 0;
  afterCursor = frontDummy;
  beforeCursor = frontDummy->prev;
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack(){
  pos_cursor = num_elements;
  beforeCursor = backDummy;
  afterCursor = backDummy->next;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
int List::peekNext(){
  if( pos_cursor >= num_elements){
   cerr << "List Error: calling peekNext on a NULL list element" << endl;
   exit(EXIT_FAILURE);
 }

  return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
int List::peekPrev(){
  if( pos_cursor == 0){
   cerr << "List Error: calling peekPrev on a NULL list element" << endl;
   exit(EXIT_FAILURE);
 }

  return beforeCursor->data;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<size()
int List::moveNext(){
  if( pos_cursor >= num_elements){
   cerr << "List Error: calling moveNext to a NULL list element" << endl;
   exit(EXIT_FAILURE);
 }

  pos_cursor++;
  beforeCursor = afterCursor;
  afterCursor = afterCursor->next;
  return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
int List::movePrev(){
  if( pos_cursor == 0){
   cerr << "List Error: calling movePrev to a NULL list element" << endl;
   exit(EXIT_FAILURE);
 }
 pos_cursor--;
 afterCursor = beforeCursor;
 beforeCursor = beforeCursor->prev;
 return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(int x){
  Node *N = new Node(x);

  if( isEmpty() ){
    frontDummy = backDummy = afterCursor = N;
    num_elements++;
    return;
  }

  N->next = afterCursor;
  afterCursor = N;
  afterCursor->prev = beforeCursor;
  N->prev = beforeCursor;
  if(afterCursor->next != NULL){
    afterCursor->next->prev = N;
  }
  if(afterCursor->prev != NULL){
    afterCursor->prev->next = N;
  }
  if(pos_cursor == num_elements){
    backDummy = afterCursor;
  }
  if(pos_cursor == 0){
    frontDummy = afterCursor;
  }
  num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(int x){
  Node *N = new Node(x);

  if( isEmpty() ){
    frontDummy = backDummy = beforeCursor = N;
    num_elements++;
    pos_cursor++;
    return;
  }

  N->prev = beforeCursor;
  beforeCursor = N;
  beforeCursor->next = afterCursor;
  N->next = afterCursor;
  if(beforeCursor->prev != NULL){
    beforeCursor->prev->next = N;
  }
  if(beforeCursor->next != NULL){
    beforeCursor->next->prev = N;
  }
  if(pos_cursor == num_elements){
    backDummy = beforeCursor;
  }
  if(pos_cursor == 0){
    frontDummy = beforeCursor;
  }
  num_elements++;
  pos_cursor++;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){
  Node *N = afterCursor;

  if( pos_cursor >= num_elements){
   cerr << "List Error: calling eraseAfter for a NULL list element" << endl;
   exit(EXIT_FAILURE);
 }

 if(afterCursor == backDummy){
   backDummy = beforeCursor;
 }
 if(afterCursor == frontDummy){
   frontDummy = frontDummy->next;
 }

 if(afterCursor->next != nullptr && afterCursor->prev != nullptr){
   afterCursor->prev->next = afterCursor->next;
   afterCursor->next->prev = afterCursor->prev;
 }

 afterCursor = afterCursor->next;
 num_elements--;
 delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
  Node *N = beforeCursor;

  if( pos_cursor == 0){
   cerr << "List Error: calling eraseBefore for a NULL list element" << endl;
   exit(EXIT_FAILURE);
  }

  if(beforeCursor == frontDummy){
    frontDummy = afterCursor;
  }
  if(beforeCursor == backDummy){
    backDummy = backDummy->prev;
    if(backDummy != nullptr){
      backDummy->next = nullptr;
    }
  }

  if(beforeCursor->next != nullptr && beforeCursor->prev != nullptr){
    beforeCursor->prev->next = beforeCursor->next;
    beforeCursor->next->prev = beforeCursor->prev;
  }

  beforeCursor = beforeCursor->prev;
  pos_cursor--;
  num_elements--;
  delete N;
}

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so
// eraseBefore() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1.
int List::findNext(int x){
  while(afterCursor->data != x){
    pos_cursor++;
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    if(pos_cursor >= num_elements){
      return -1;
    }
  }

  pos_cursor++;
  beforeCursor = afterCursor;
  afterCursor = afterCursor->next;
  return pos_cursor;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so
// eraseAfter() would remove the found element), and returns the final
// cursor position. If x is not found, places the cursor at position 0, and
// returns -1.
int List::findPrev(int x){
  while(beforeCursor->data != x){
    pos_cursor--;
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    if(pos_cursor == 0){
      return -1;
    }
  }

  pos_cursor--;
  afterCursor = beforeCursor;
  beforeCursor = beforeCursor->prev;

  return pos_cursor;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other
// occurances. The cursor is not moved with respect to the retained
// elements, i.e. it lies between the same two retained elements that it
// did before cleanup() was called.
void List::cleanup(){
  int pos = pos_cursor;

  int count = 0;
  moveFront();
  while(count < num_elements){
    for(int i = 0; i < count; i++){
      moveNext();
    }
    int data = afterCursor->data;
    moveNext();
    while( pos_cursor < num_elements){
      moveNext();
      if(beforeCursor->data == data){
        eraseBefore();
        if(pos_cursor < pos){
          pos--;
        }
      }
    }

    moveFront();
    count++;
  }
  for(int i = 0; i < pos; i++){
    moveNext();
  }
}

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
  if(!isEmpty()){
    moveBack();
    while(!isEmpty()){
      eraseBefore();
    }
  }
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L){
  List J;
  Node *N = this->frontDummy;
  Node *M = L.frontDummy;
  while (N != nullptr){
    J.insertBefore(N->data);
    N = N->next;
  }
  while (M != nullptr){
    J.insertBefore(M->data);
    M = M->next;
  }
  J.moveFront();
  return J;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string(){
  Node *N = nullptr;
  string s = "";

  for(N = frontDummy; N != nullptr; N = N->next){
    s += std::to_string(N->data)+" ";
  }

  return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R){
  bool eq = false;
  Node *N = nullptr;
  Node *M = nullptr;

  eq = ( this->num_elements == R.num_elements);
  N = this->frontDummy;
  M = R.frontDummy;
  while(eq && N != nullptr && M != nullptr){
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }

  return eq;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, List& L ){
  return stream << L.List::to_string();;
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged are unchanged.
bool operator==( List& A, const List& B ){
  return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
  if( this != &L){
    List temp = L;

    std::swap(frontDummy, temp.frontDummy);
    std::swap(backDummy, temp.backDummy);
    std::swap(beforeCursor, temp.beforeCursor);
    std::swap(afterCursor, temp.afterCursor);
    std::swap(num_elements, temp.num_elements);
    std::swap(pos_cursor, temp.pos_cursor);
  }

  return *this;
}
