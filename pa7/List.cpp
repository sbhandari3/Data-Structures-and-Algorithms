/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA7
* List.cpp
*********************************************************************************/
#include<iostream>
#include<string>
#include"List.h"

using namespace std;

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(int x){
   next = nullptr;
   prev = nullptr;

   data = x;
   
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List(){
   frontDummy = new Node (-1);
   backDummy = new Node (1000);

   frontDummy -> next = backDummy;
    backDummy -> prev = frontDummy;

   beforeCursor = frontDummy;
   afterCursor = backDummy;

   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   frontDummy = new Node (-1);
   backDummy = new Node (1000);

   beforeCursor = frontDummy;
   afterCursor = backDummy;

   frontDummy -> next = backDummy;
    backDummy -> prev = frontDummy;


   pos_cursor = 0;
   num_elements = 0;

   // load elements of L into this
   Node* N = L.frontDummy->next;

   while( N!=L.backDummy ){
      this->insertBefore(N->data);
      N = N->next;
   }
   this->moveFront();
}

void clear();

// Destructor
List::~List(){
   clear();

   delete frontDummy;
   delete backDummy;
}

// Access functions -----------------------------------------------------------

 // isEmpty()
   // Returns true if this List is empty, false otherwise.
bool List::isEmpty(){
   if(num_elements == 0){
	return true;
   }
   else{
	return false;
   }
}


// size()
// Returns the size of this List.
int List::size(){
  
  return(num_elements);
  
}

   // position()
   // Returns the position of the cursor in this List. The value returned
   // will be in the range 0 to size().
int List::position(){
  
  return (pos_cursor);
  
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
  
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
	
}

// moveBack()
   // Moves cursor to position size() in this List.
void List::moveBack(){
 
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
	pos_cursor = num_elements;
	
}

// peekNext()
 // Returns the element after the cursor.
// pre: position()<size()
int List::peekNext(){
  
   if(pos_cursor < num_elements){
	return afterCursor->data;
  } 
   else {
	exit(EXIT_FAILURE);
  }
  
}

// peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
int List::peekPrev(){
   if(pos_cursor > 0){  
	return beforeCursor->data;
   } 
   else {
	  exit(EXIT_FAILURE); 
  }
}

// moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<size() 
int List::moveNext(){
  
  if(pos_cursor < num_elements){
	pos_cursor++;
	afterCursor = afterCursor->next;
	beforeCursor = beforeCursor->next;
	return (beforeCursor->data);	  
  }
  
}

// movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
int List::movePrev(){
  if(pos_cursor > 0){
	pos_cursor--;
	afterCursor = afterCursor->prev;
	beforeCursor = beforeCursor->prev;
	return afterCursor->data;
    
  }
  
}


// insertAfter()
   // Inserts x after cursor.
void List::insertAfter(int x){
  
  Node* temp = new Node(x);
  temp->prev = beforeCursor;
  temp->next = afterCursor;
  afterCursor->prev = temp;
  beforeCursor->next = temp;
  afterCursor = temp;
  num_elements++;
}

// insertBefore()
   // Inserts x before cursor.
void List::insertBefore(int x){
	
	
  Node* temp = new Node(x);
  temp->prev = beforeCursor;
  temp->next = afterCursor;
  beforeCursor->next = temp;
  afterCursor->prev = temp;
  beforeCursor = temp;
  num_elements++;
  pos_cursor++;	
}

// eraseAfter()
   // Deletes element after cursor.
   // pre: position()<size()
void List::eraseAfter(){
  
  if(pos_cursor == num_elements || num_elements == 0){
	exit(EXIT_FAILURE);
  }
  Node* after = afterCursor;
  Node* afterNext = afterCursor->next;;
  Node* before = beforeCursor;

  before->next = afterNext;
  afterNext->prev = before;
  afterCursor = afterNext;
  delete after;
  num_elements--; 
}


// eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
void List::eraseBefore(){
  if(pos_cursor == 0 || num_elements == 0){
        exit(EXIT_FAILURE);
  }
  Node* before = beforeCursor;
  Node* beforePrev = before->prev;
  Node* after = afterCursor;

  beforePrev->next = after;
  after->prev = beforePrev;
  beforeCursor = beforePrev;
  delete before;
  pos_cursor--;
  num_elements--;
}


// findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of the element x.
   // If x is found, places the cursor immediately after the found element (so 
   // eraseBefore() would remove the found element), and returns the final 
   // cursor position. If x is not found, places the cursor at position size(),
   // and returns -1. 
int List::findNext(int x){
   if(pos_cursor == num_elements){
	return -1;
   }
   int mNext; 
   mNext = moveNext();
   while(pos_cursor < num_elements){
	if(mNext == x){
		return pos_cursor;
	}
	mNext = moveNext();
   }
   return -1;    
}

// findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of the element x.
   // If x is found, places the cursor immediately before the found element (so 
   // eraseAfter() would remove the found element), and returns the final 
   // cursor position. If x is not found, places the cursor at position 0, and 
   // returns -1. 
int List::findPrev(int x){
   Node* N;
   N = afterCursor;
   movePrev();
   while(pos_cursor != 0){
	N = afterCursor;
		if(N->data == x){
			return pos_cursor;
		}
		movePrev();
	}
	if(afterCursor->data != x){
		return -1;
	}
	else{
		return pos_cursor;
	} 
}

// cleanup()
   // Removes any repeated elements in this List, leaving only unique data
   // values. The order of the remaining elements is obtained by retaining
   // the frontmost occurrance of each element, and removing all other 
   // occurances. The cursor is not moved with respect to the retained 
   // elements, i.e. it lies between the same two retained elements that it 
   // did before cleanup() was called.
void List::cleanup(){
	Node* save;
	save = nullptr;
	Node* A;
        A = nullptr;
	Node* goNext;
        goNext = frontDummy->next;	
	
	while(goNext != backDummy){
		A = goNext->next;
		save = goNext;
		while(A != backDummy){
			if(A->data == goNext->data){
				num_elements--;
				A->next->prev = save;
				save->next = A->next;
				if(A == beforeCursor){
					pos_cursor--;
					beforeCursor = save;
				}
				if(A == afterCursor){									afterCursor = A->next;
				}
				delete A;
				A = save->next;
			}
			else{
				save = A;
				A = save->next;
			}
		}
		goNext = goNext->next;
	}
}
  

// clear()
   // Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	
	Node* front = frontDummy->next;
	Node* null = nullptr;
	
	while(front != backDummy){
		null = front;
		front = front->next;
		delete null;
	}
   frontDummy->next = backDummy;
   //frontDummy->prev = nullptr;
   //backDummy->next = nullptr;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0; 
 
}

// concat()
   // Returns a new List consisting of the elements of this List, followed
   // the elements of L. The returned List's cursor will be at its front
   // (position 0).
List List::concat(const List& L){
  List A;
  Node* one;
  Node* two;
  one = this->frontDummy->next;
  two = L.frontDummy->next;
  
  while(one != this->backDummy){
	A.insertBefore(one->data);
	one = one->next;
  }
  while(two!= L.backDummy){
        A.insertBefore(two->data);
        two = two->next;
  }
  A.moveFront();
  A.num_elements = this->num_elements + L.num_elements;
  return A; 
}


// Other Functions ------------------------------------------------------------

// to_string()
// Returns a string representation of Queue consisting of a space separated 
// list of data values.
string List::to_string(){
	Node* N = nullptr;
   string s = "";

   for(N=frontDummy; N!=nullptr; N=N->next){
      s += std::to_string(N->data)+" ";
   }
   
   return s;
	 
}

// equals()
// Returns true if and only if this is the same integer sequence as Q.
bool List::equals(const List& Q){
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;


   eq = ( this->num_elements == Q.num_elements );
   N = this->frontDummy;
   M = Q.frontDummy;
   while( eq && N!=nullptr){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   
   
   return eq;
}


// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of Q into stream.
ostream& operator<< ( ostream& stream,  List& Q ) {
   return stream << Q.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B.
bool operator== (List& A, const List& B){
   return A.List::equals(B);
}

// operator=()
// Overwrites the state of this Queue with state of Q.
List& List::operator=( const List& L ) {
	
	
   if( this != &L ){ // not self assignment
      // make a copy of Q
      List temp = L;
		
      // then swap the copy's fields with fields of this
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
   }
  

   // return this with the new data installed
   return *this;

   // the copy, if there is one, is deleted upon return
}
