/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA1
* List.c
* List.c has methods for Lex.c
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"


// PRIVATE TYPES -------------------------------------

// NodeObj
typedef struct NodeObj {
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
}
NodeObj;

// Node
typedef NodeObj* Node;

// ListObj
typedef struct ListObj {
    // initialize variable
    Node head;  // front element
    Node back;  // back element
    Node cursor;    // cursor 
    int length;     // # of elements
    int index;    // index 
} ListObj;


// Constructors-Destructors -------------------------------------

// new Node ()
// constructor
Node newNode (int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return(N);
}
// freeNode ()
// destructor
void freeNode (Node* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}
// newList()
// Creates and returns a new empty List
List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->head = NULL;
    L->back = NULL;
    L-> cursor = NULL;
    L-> index = -1;  
    L->length = 0; 
    return(L);
}
// freeList()
// Frees all heap memory associated with *pL
// sets *pL to NULL
void freeList(List* pL) {
    if (pL!=NULL && *pL!=NULL) {
        while(length(*pL) > 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}


// Access functions -------------------------------------
// length()
// returns the number of elements in L
int length(List L) {
    if (L == NULL) {
        printf("List error: calling length() on NULL List reference\n");
        exit(1);
    }
    return L->length;
}
// index()
// Returns number of index cursor element if defined
// -1 otherwise (undefined)
// pre: length() > 0
int index(List L) {
    if (L == NULL) {
        printf("List error: calling index() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0){
        return -1;
    }
    return L->index;
}
// front()
// returns front element of L
// pre: length() > 0
int front(List L) {
    if (L == NULL) {
        printf("List error: calling front() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0) {
        printf(" List error: front() called on empty List\n");
        exit(1);
    }
    return L->head->data;
}
// back()
// returns back element of L
// pre: length() > 0
int back(List L) {
    if (L == NULL) {
        printf("List error: calling back() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0) {
        printf(" List error: back() called on empty List\n");
        exit(1);
    }
    return L->back->data;
}
// get()
// returns cursor element of L
// pre: length()>0 and index()>=0
int get(List L) {
    if (L == NULL) {
        printf("List error: calling get() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0) {
        printf(" List error: get() called on empty List\n");
        exit(1);
    }
    if (L->cursor == NULL) {
        printf(" List error: get() called on NULL cursor\n");
        exit(1);
    }
    return L->cursor->data;
}
// equals()
// returns true (1) iff Lists A and B are in same state
// false (0) otherwise
int equals (List A, List B) {
    int equals = 0;
    Node N;
    Node S;
    
    if (A==NULL || B==NULL) {
        printf("List error: calling equals() on NULL List reference");
        exit(1);
    }
    if(A->length != B-> length){
        return 0;
    }
    equals = (A->length == B->length);
    N = A->head;
    S = B->head;
    while(equals && N!=NULL) {
        equals = (N->data == S->data);
        N = N->next;
        S = S->next;
    }
    return equals;
}


// Manipulation procedures ----------------------------------------------
// clear()
// Resets L ro original empty state
void clear(List L) {
    if (L == NULL) {
        printf("List error: calling clear() on NULL List reference\n");
        exit(1);
    }
    while (length(L) > 0) {
        deleteFront(L);
    }
    L->head = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}
// moveFront()
// if L is non-empty, sets cursor under the front element
// otherwise does nothing
// pre: length() > 0
void moveFront(List L) {
    if (L == NULL) {
        printf("List error: calling moveFront() on NULL List reference\n");
        exit(1);
    }
    if (length(L) > 0) {
        L->cursor = L->head;
        L->index = 0;
    }
}
// moveBack()
// if L is non-empty, sets cursor under back element
// otherwise nothing
// pre: length()>0
void moveBack(List L) {
    if (L == NULL) {
        printf("List error: calling moveBack() on NULL List reference\n");
        exit(1);
    }
    if (length(L) > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}
// movePrev()
// if cursor is defined and NOT AT front
// move cursor one step toward front of L
// if cursor is defined and AT front
// cursor becomes undefined
// if cursor is undefined, do nothing
void movePrev(List L) {
    if (L == NULL) {
        printf("List error: calling movePrev() on NULL List reference\n");
        exit(1);
    }
    if (L->cursor == L->head) {
	L->cursor = NULL;
        L->index = -1;
    }
    else {
    	L->cursor = L->cursor->prev;
        L->index--;
    }
}
// moveNext()
// if cursor is defined and NOT AT back
// move cursor one step toward back
// if cursor is defined and AT back
// cursor becomes undefined
// if undefined, do nothing
void moveNext(List L) {
    if (L == NULL) {
        printf("List error: calling moveNext() on NULL List reference\n");
        exit(1);
    }
    if (L->cursor != L->back) {
        L->cursor = L->cursor->next;
        L->index++;
    }
    else {
        L->cursor = NULL;
        L->index = -1;
    }
}
// prepend()
// insert new element into L
// if L is non-empty, insertion before front element
void prepend(List L, int data) {
    Node N = newNode(data);
    if (L == NULL) {
        printf("List error: calling prepend() on NULL List reference\n");
        exit(1);
    }
    if (L->head == NULL) {
        L->head = N;
        L->back = N;
        L->cursor = L->head;
    }
    else {
        L->head->prev = N;
        N->next = L->head;
        L->head = N;
        L->index++;
    }
    L->length++;
}
// append()
// insert new element into L
// if L is non-empty, insert after back element
void append(List L, int data) {
    if (L == NULL) {
        printf("List error: calling append() on NULL List reference\n");
        exit(1);
    }
    Node N = newNode(data);
    if (L->back == NULL) {
        L->head = N;
        L->back = N;
        L->cursor = L->back;
    }
    else {
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
        N->next = NULL;
    }
    L->length++;
}
// insertBefore()
// insert new element before cursor
// pre: length()>0, index()>=0
void insertBefore(List L, int data) {
    if (L == NULL) {
        printf("List error: calling insertBefore() on NULL List reference\n");
        exit(1);
    }
    if (L->cursor == NULL) {
        printf("List error: calling insertBefore() on undefined cursor\n");
        exit(1);
    }
    if (L->cursor != L->head) {
	Node N = newNode(data);
        N->prev = L->cursor->prev;
        N->next = L->cursor;
        L->cursor->prev->next = N;
        L->cursor->prev = N;
        L->index++;
        L->length++;
    }
    else {
	prepend(L, data);
    }
}
// insertAfter()
// insert new element after cursor
// pre: length()>0, index()>=0
void insertAfter (List L, int data) {
    if (L == NULL) {
        printf("List error: calling insertAfter() on NULL List reference\n");
        exit(1);
    }
    if (L->cursor == NULL) {
        printf("List error: calling insertAfter() on undefined cursor\n");
        exit(1);
    }
    if (L->cursor != L->back) {
        Node N = newNode(data);
        L->cursor->next->prev = N;
        N->next = L->cursor->next;
        N->prev = L->cursor;
        L->cursor->next = N;
        L->length++;
    }
    else {
	append(L, data);
    }
}
// deleteFront()
// delete the front element
// pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        printf("List error: calling deleteFront() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0) {
        printf(" List error: deleteFront() called on empty List\n");
	exit(1);
    }
    else {
        if (L->length == 1) {
            Node N = L->head; 
            freeNode(&N); 
            L->cursor = NULL; 
            L->head = NULL;
            L->back = NULL;
            L->index = -1;
        }
        else {
            Node N = L->head;
            L->head = L->head->next; 
            L->head->prev = NULL; 
            if (L->cursor != NULL) {
                L->index--;
            }
            freeNode(&N);
        }
        L->length--;
    }
}
// deleteBack()
// delete the back element
// pre: length()>0
void deleteBack(List L) {
    if (L == NULL) {
        printf("List error: calling deleteBack() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0) {
        printf(" List error: deleteBack() called on empty List\n");
	exit(1);
    }
    else {
        if (L->length == 1) {
            Node N = L->back; 
            freeNode(&N); 
            L->cursor = NULL; 
            L->head = NULL;
            L->back = NULL;
            L->index = -1;
        }
        else {
            Node N = L->back;
            L->back = L->back->prev;
            L->back->next = NULL; 
            if (L->index == L->length-1) {
                L->index = -1;
            }
            freeNode(&N);
        }
        L->length--;
    }
}
// delete()
// delete cursor element, making cursor undefined
// pre: length()>0, index()>=0
void delete(List L) {
    if (L == NULL) {
        printf("List error: calling delete() on NULL List reference\n");
        exit(1);
    }
    if (length(L) <= 0 || L->cursor == NULL) {
        printf(" List error: deleteBack() called on empty List\n");
    }
    if (L->cursor == L->head){
        deleteFront(L);
    }
    else if (L->cursor == L->back){
        deleteBack(L);
    }
    else{
        Node S = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&S);
        L->length--;
    }
    L->index = -1;
}


// Other operation -----------------------------------------------------------
// printList()
// prints to file pointed to by out
// string rep of L consisting of space seperated sequence of ints
// front on left
void printList(FILE* out, List L) {
    Node N = NULL;
    if (L == NULL) {
        printf("List error: calling printList() on NULL List reference\n");
        exit(1);
    }
    for (N = L->head; N!=NULL; N=N->next) {
        fprintf(out," %d", N->data);
        fprintf(out, " ");
    }
}
// copyList()
// returns new List seperating same integer sequence as L
// cursor in new List is undefined
// state of L unchanged
List copyList(List L) {
    if (L == NULL) {
        printf("List error: calling copyList() on NULL List reference\n");
        exit(1);
    }
    Node N = L->head;
    List Copy = newList();
    if (length(L) > 0) {    
        while ( N != NULL) {
            append(Copy, N->data);
            N = N->next; 
        }
    }
    return Copy;
}

