/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA5
* Dictionary.c
* Dictionary.c has methods to create a Dictionary ADT
*********************************************************************************/

//-----------------------------------------------------------------------------
// Dictionary.c
// Header file for Dictionary ADT storing (key, value) pairs of types KEY_TYPE 
// and VAL_TYPE.  
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include"Dictionary.h"

#define KEY_TYPE char*
#define VAL_TYPE int
#define KEY_UNDEF NULL
#define VAL_UNDEF -1
#define KEY_FORMAT "%s"
#define VAL_FORMAT "%d"
#define KEY_CMP(x,y) strcmp((x),(y))

// NodeObj type
typedef struct NodeObj{
   KEY_TYPE key;
   VAL_TYPE val;
   struct NodeObj* left;
   struct NodeObj* right;
   struct NodeObj* parent;
} NodeObj;

// Node type
typedef NodeObj* Node;

// DictionaryObj type
typedef struct DictionaryObj{
   Node root;         // pointer to first Node in Dictionary
   int size;      // number of items in this Dictionary
   int unique;
   Node cursor;
} DictionaryObj;

// newNode()
// constructor for the Node type
Node newNode(KEY_TYPE k, VAL_TYPE v) {
   Node N = malloc(sizeof(NodeObj));
   N->key = k;
   N->val = v;
   N->right = NULL;
   N->left = NULL;
   return N;
}
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}
void emptyTree(Node P){
   if(P != NULL){
        emptyTree(P->left);
        emptyTree(P->right);
        freeNode(&P);
   }
}

// Exported type --------------------------------------------------------------
typedef struct DictionaryObj* Dictionary;


// Constructors-Destructors ---------------------------------------------------

// newDictionary()
// Creates a new empty Dictionary. If unique==false (0), then the Dictionary 
// will accept duplicate keys, i.e. distinct pairs with identical keys. If 
// unique==true (1 or any non-zero value), then duplicate keys will not be 
// accepted. In this case, the operation insert(D, k) will enforce the 
// precondition: lookup(D, k)==VAL_UNDEF
Dictionary newDictionary(int unique){
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->root = NULL;
   D->size = 0;
   D->unique = unique;
   D->cursor = NULL;

   return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
         makeEmpty(*pD);
         free(*pD);
         *pD = NULL;
   }
 }

Node findKey(Dictionary D, KEY_TYPE k){
   if(D == NULL || D->size == 0){
	return NULL;
   }
   Node N;
   N = D->root;
   while(N !=NULL){
   	if(KEY_CMP(k, N->key) == 0){
		return N;
   	}	
   	if(KEY_CMP(k, N->key) > 0){
		N = N->left;
  	}
   	else{
		N = N->right;
   	}
   }
}

Node treeSearch(Node x, KEY_TYPE k){
   if(x == NULL || KEY_CMP(x->key, k) == 0){
	return x;
   }
   else if (KEY_CMP(x->key, k) > 0){
	return treeSearch(x->left,k);
   }
   else{
	return treeSearch(x->right,k);
   }	
}

Node treeMin(Node X){
    if(X == NULL){
        return NULL;
   }
   while(X->left != NULL){
	X = X->left;
   }
   return X;
}

Node treeMax(Node X){
   if(X == NULL){
	return NULL;
   }
   while(X->right != NULL){
        X = X->right;
   }
   return X;
}

Node treeSuccessor(Node X){
   if(X == NULL){
        return NULL;
   }
   if(X->right != NULL){
	return treeMin(X->right);
   }
   Node Y;
   Y = X->parent;
   while(Y != NULL && X == Y->right){
	X = Y;
	Y = Y->parent;
   }
   return Y;
}

Node treePred(Node X){
   if(X == NULL){
        return NULL;
   }
   if(X->left != NULL){
        return treeMax(X->left);
   }
   Node Y;
   Y = X->parent;
   while(Y != NULL && X == Y->left){
        X = Y;
        Y = Y->parent;
   }
   return Y;
}

void Transplant(Dictionary D, Node u, Node v){
   if(u->parent == NULL){
	D->root = v;
   }
   else if(u == u->parent->left){
	u->parent->left = v;
   }
   else{
	u->parent->right = v;
   }
   if(v != NULL){
	v->parent = u->parent;
   }
}
// Access functions -----------------------------------------------------------

// size()
// Returns the number of (key, value) pairs in Dictionary D.
int size(Dictionary D){
	if( D==NULL ){
      fprintf(stderr, "Dictionary Error: size() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }

   return D->size;
}

// getUnique()
// Returns true (1) if D requires that all pairs have unique keys. Returns
// false (0) if D accepts distinct pairs with identical keys.
int getUnique(Dictionary D){
    if( D==NULL ){
      fprintf(stderr, "Dictionary Error: size() called on NULL Dictionary reference");
      exit(EXIT_FAILURE); 
    }  
    if(D->unique == 0){
   	return 0;
   }
   else{
   	return 1;
   }
}

// lookup()
// If Dictionary D contains a (key, value) pair whose key matches k (i.e. if
// KEY_CMP(key, k)==0), then returns value. If D contains no such pair, then
// returns VAL_UNDEF.
VAL_TYPE lookup(Dictionary D, KEY_TYPE k){
   if( D==NULL ){
      return VAL_UNDEF;
   }
   Node N = D->root;
   while(N != NULL){
	if(KEY_CMP(N->key,k) == 0){
		return N->val;
	}
	if(KEY_CMP(N->key, k) > 0){
		N = N->left;
	}
	else{
		N = N->right;
	}
   }
   if(N == NULL) {
       return VAL_UNDEF;
   }
}


// Manipulation procedures ----------------------------------------------------

// insert()
// Insert the pair (k,v) into Dictionary D. 
// If getUnique(D) is false (0), then there are no preconditions.
// If getUnique(D) is true (1), then the precondition lookup(D, k)==VAL_UNDEF
// is enforced. 
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: insert() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);   
   }
   if(getUnique(D) == 1){
	if(lookup(D,k) != VAL_UNDEF){
		fprintf(stderr, "Dictionary Error: insert() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
     	}
   }
   Node X;
   Node	Y;
   Node Z;
   Y = NULL;
   X = D->root;
   Z = newNode(k,v);
   while(X != NULL){
	Y = X;
	if(KEY_CMP(Z->key,X->key) < 0){
		X = X->left;
	}
	else{
		X = X->right;
	}
   }
   Z->parent = Y;
   if(Y == NULL){
	D->root = Z;
   }
   else if(KEY_CMP(Z->key, Y->key) < 0){
	Y->left = Z;
   }
   else{
	Y->right = Z;
   }
   D->size++;
}
// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
   if(D == NULL || lookup(D,k) == VAL_UNDEF){
	return;
   }
   Node Z = treeSearch(D->root,k);
   Node Y;
   if(Z == NULL){
	return;
   }
   if(Z->left == NULL){
	Transplant(D, Z, Z->right);
   }
   else if(Z->right == NULL){
	Transplant(D,Z,Z->left);
   }
   else{
	Y = treeMin(Z->right);
	if(Y->parent != Z){
		Transplant(D,Y,Y->right);
		Y->right = Z->right;
		Y->right->parent = Y;
	}
	Transplant(D,Z,Y);
	Y->left = Z->left;
	Y->left->parent = Y;
   }
   D->size--;
   if(D->cursor == Z){
	D->cursor = NULL;
   }
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: makeEmpty() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }   
   emptyTree(D->root);
   D->root = NULL;
   D->size = 0;
   D->cursor = NULL;
}



// beginForward()
// If D is non-empty, starts a forward iteration over D at the first key 
// (as defined by the order operator KEY_CMP()), then returns the first
// value. If D is empty, returns VAL_UNDEF. 
VAL_TYPE beginForward(Dictionary D){
   if(D == NULL){
	return VAL_UNDEF;
   }
   Node X;
   X = treeMin(D->root);
   D->cursor = X;
   if(X == NULL){
	return VAL_UNDEF;
   }
   return X->val;
}

// beginReverse()
// If D is non-empty, starts a reverse iteration over D at the last key 
// (as defined by the order operator KEY_CMP()), then returns the last
// value. If D is empty, returns VAL_UNDEF.
VAL_TYPE beginReverse(Dictionary D){
   if(D == NULL){
        return VAL_UNDEF;
   }
   Node X;
   X = treeMax(D->root);
   D->cursor = X;
   if(X == NULL){
        return VAL_UNDEF;
   }
   return X->val;
}


// currentKey()
// If an iteration (forward or reverse) over D has started, returns the 
// the current key. If no iteration is underway, returns KEY_UNDEF.
KEY_TYPE currentKey(Dictionary D){
   if(D == NULL){
	return KEY_UNDEF;
   }
   if(D->cursor == NULL){
        return KEY_UNDEF;
   }
   return D->cursor->key;
}

// currentVal()
// If an iteration (forward or reverse) over D has started, returns the 
// value corresponding to the current key. If no iteration is underway, 
// returns VAL_UNDEF.
VAL_TYPE currentVal(Dictionary D){
   if(D == NULL){
        return VAL_UNDEF;
   }
   if(D->cursor == NULL){
        return VAL_UNDEF;
   }
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
   if(D == NULL){
	return VAL_UNDEF;
   }
   if(D->cursor == NULL){
   	return VAL_UNDEF;
   }
   D->cursor = treeSuccessor(D->cursor);
   if(D->cursor == NULL){
        return VAL_UNDEF;
   }
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
   if(D == NULL){
        return VAL_UNDEF;
   }
   if(D->cursor == NULL){
        return VAL_UNDEF;
   }
   D->cursor = treePred(D->cursor);
   if(D->cursor == NULL){
        return VAL_UNDEF;
   }
   return D->cursor->val;
}


// Other operations -----------------------------------------------------------

// printDictionary()
// Prints a text representation of D to the file pointed to by out. Each key-
// value pair is printed on a single line, with the two items separated by a
// single space.  The pairs are printed in the order defined by the operator
// KEY_CMP().
void printDictionary(FILE* out, Dictionary D){
   Node X;
   X = treeMin(D->root);
   while(X != NULL){
   	fprintf(out, "" KEY_FORMAT " " VAL_FORMAT "\n",X->key, X->val);
	X = treeSuccessor(X);
   }
}



