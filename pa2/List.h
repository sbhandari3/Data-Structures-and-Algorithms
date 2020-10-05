/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA2
* List.h
* List.h is a header file
*********************************************************************************/
//-----------------------------------------------------------------------------
// List.h
// Header file for the List ADT in C
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------

// Creates and returns a new empty List.
List newList(void); 

// Frees all heap memory associated with *pL, and sets
 // *pL to NULL.
void freeList(List* pL);

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
long length(List L); 

// Returns index of cursor element if defined, -1 otherwise.
long index(List L); 

// Returns front element of L. Pre: length()>0
long front(List L);

// Returns back element of L. Pre: length()>0
long back(List L); 

// Returns cursor element of L. Pre: length()>0, index()>=0
long get(List L); 

// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
//long equals(List A, List B); 


// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L); 


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
void prepend(List L, long data); 


 // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void append(List L, long data);

 
// Insert new element before cursor.
 // Pre: length()>0, index()>=0
void insertBefore(List L, long data);

// Insert new element after cursor.
 // Pre: length()>0, index()>=0
void insertAfter(List L, long data); 


// Delete the front element. Pre: length()>0
void deleteFront(List L); 

// Delete the back element. Pre: length()>0
void deleteBack(List L); 

// Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0
void delete(List L); 

// Other operations -----------------------------------------------------------

// Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L); 

// Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L); 

#endif // LIST_H_INCLUDED
