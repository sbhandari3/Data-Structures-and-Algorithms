/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA6
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

#define RED 1
#define BLACK 0
#define KEY_TYPE char*
#define VAL_TYPE int*
#define KEY_UNDEF NULL
#define VAL_UNDEF NULL
#define KEY_FORMAT "%s"
#define VAL_FORMAT "%p"
#define KEY_CMP(x,y) strcmp(x,y)

// NodeObj type
typedef struct NodeObj{
   KEY_TYPE key;
   VAL_TYPE val;
   struct NodeObj* left;
   struct NodeObj* right;
   struct NodeObj* parent;
   int color;
} NodeObj;

// Node type
typedef NodeObj* Node;

// DictionaryObj type
typedef struct DictionaryObj{
   Node root;         // pointer to first Node in Dictionary
   int size;      // number of items in this Dictionary
   int unique;
   Node cursor;
   Node NIL;
   
} DictionaryObj;

// newNode()
// constructor for the Node type
Node newNode(KEY_TYPE k, VAL_TYPE v) {
   Node N = malloc(sizeof(NodeObj));
   N->key = k;
   N->val = v;
   N->right = NULL;
   N->left = NULL;
   N->parent = NULL;
   N->color = -1;
   return N;
}
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
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
   D->NIL = newNode(KEY_UNDEF, VAL_UNDEF);
   D->NIL->color = BLACK;
   D->root = D->NIL;;
   D->size = 0;
   D->unique = unique;
   D->cursor = D->NIL;

   return D;
}

// freeDictionary()
// Frees heap memory associated with *pD, sets *pD to NULL.
void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
         makeEmpty(*pD);
	 freeNode(&(*pD)->NIL);
         free(*pD);
         *pD = KEY_UNDEF;
   }
 }

void emptyTree(Dictionary D,Node P){
   if(P != D->NIL){
        emptyTree(D,P->left);
        emptyTree(D,P->right);
        freeNode(&P);
   }
}

Node treeSearch(Dictionary D, Node x, KEY_TYPE k){
   if(x == D->NIL || KEY_CMP(x->key, k) == 0){
	return x;
   }
   else if (KEY_CMP(x->key, k) > 0){
	return treeSearch(D,x->left,k);
   }
   else{
	return treeSearch(D,x->right,k);
   }	
}

Node treeMin(Dictionary D, Node X){
    if(X == D->NIL){
        return D->NIL;
   }
   while(X->left != D->NIL){
	X = X->left;
   }
   return X;
}

Node treeMax(Dictionary D, Node X){
   if(X == D->NIL){
	return D->NIL;
   }
   while(X->right != D->NIL){
        X = X->right;
   }
   return X;
}

Node treeSuccessor(Dictionary D, Node X){
   if(X == D->NIL){
        return D->NIL;
   }
   if(X->right != D->NIL){
	return treeMin(D,X->right);
   }
   Node Y;
   Y = X->parent;
   while(Y != D->NIL && X == Y->right){
	X = Y;
	Y = Y->parent;
   }
   return Y;
}

Node treePred(Dictionary D, Node X){
   if(X == D->NIL){
        return D->NIL;
   }
   if(X->left != D->NIL){
        return treeMax(D,X->left);
   }
   Node Y;
   Y = X->parent;
   while(Y != D->NIL && X == Y->left){
        X = Y;
        Y = Y->parent;
   }
   return Y;
}

void LeftRotate(Dictionary D, Node x){
   Node y = x->right;
   x->right = y->left;
   if(y->left != D->NIL){
	y->left->parent = x;
   }
   y->parent = x->parent;
   if(x->parent == D->NIL){
	D->root = y;
   }
   else if(x == x->parent->left){
	x->parent->left = y;
   }
   else{
 	x->parent->right = y;
   }
   
   y->left = x;
   x->parent = y;
}

void RightRotate(Dictionary D, Node x){
   Node y = x->left;
   x->left = y->right;
   if(y->right != D->NIL){
        y->right->parent = x;
   }
   y->parent = x->parent;
   if(x->parent == D->NIL){
        D->root = y;
   }
   else if(x == x->parent->right){
        x->parent->right = y;
   }
   else{
        x->parent->left = y;
   }

   y->right = x;
   x->parent = y;
}

void Transplant(Dictionary D, Node u, Node v){
   if(u->parent == D->NIL){
	D->root = v;
   }
   else if(u == u->parent->left){
	u->parent->left = v;
   }
   else{
	u->parent->right = v;
   }
   v->parent = u->parent;
}

void InsertFixUp(Dictionary D, Node z){
  Node y;
  while (z->parent->color == RED){
      if (z->parent == z->parent->parent->left){
         y = z->parent->parent->right;
         if(y->color == RED){
            z->parent->color = BLACK;              // case 1
            y->color = BLACK;                     // case 1
            z->parent->parent->color = RED;         // case 1
            z = z->parent->parent;
	}                 // case 1
         else{ 
            if(z == z->parent->right){
               z = z->parent;                     // case 2
               LeftRotate(D, z);
	    }                 // case 2
            z->parent->color = BLACK;              // case 3
            z->parent->parent->color = RED;         // case 3
            RightRotate(D, z->parent->parent);     // case 3
	 }
      }
      else{ 
         y = z->parent->parent->left;
         if (y->color == RED){
            z->parent->color = BLACK;              // case 4
            y->color = BLACK;                     // case 4
            z->parent->parent->color = RED;         // case 4
            z = z->parent->parent;
	}                 // case 4
         else{ 
            if (z == z->parent->left){
               z = z->parent;                     // case 5
               RightRotate(D, z);
	    }                // case 5
            z->parent->color = BLACK;              // case 6
            z->parent->parent->color = RED;         // case 6
            LeftRotate(D, z->parent->parent);
	 }
      }
   }      // case 6
   D->root->color = BLACK;
}

void DeleteFixUp(Dictionary D, Node x){
   Node w;
   while (x != D->root && x->color == BLACK){
      if (x == x->parent->left){
         w = x->parent->right;
         if (w->color == RED){
            w->color = BLACK;                        // case 1
            x->parent->color = RED;                   // case 1
            LeftRotate(D, x->parent);                // case 1
            w = x->parent->right;
	 }                    // case 1
         if (w->left->color == BLACK && w->right->color == BLACK){
            w->color = RED;                          // case 2
            x = x->parent;
	 }                           // case 2
         else{ 
            if (w->right->color == BLACK){
               w->left->color = BLACK;                // case 3
               w->color = RED;                       // case 3
               RightRotate(D, w);                   // case 3
               w = x->parent->right;
	    }                  // case 3
            w->color = x->parent->color;               // case 4
            x->parent->color = BLACK;                 // case 4
            w->right->color = BLACK;                  // case 4
            LeftRotate(D, x->parent);                // case 4
            x = D->root;
	 } 
      }                            // case 4
      else{ 
         w = x->parent->left;
         if (w->color == RED){
            w->color = BLACK;                        // case 5
            x->parent->color = RED;                   // case 5
            RightRotate(D, x->parent);               // case 5
            w = x->parent->left;
	 }                      // case 5
         if (w->right->color == BLACK && w->left->color == BLACK){
            w->color = RED;                          // case 6
            x = x->parent;
    	 }                           // case 6
         else{ 
            if (w->left->color == BLACK){
               w->right->color = BLACK;               // case 7
               w->color = RED;                       // case 7
               LeftRotate(D, w);                    // case 7
               w = x->parent->left;
	    }                   // case 7
            w->color = x->parent->color;               // case 8
            x->parent->color = BLACK;                 // case 8
            w->left->color = BLACK;                   // case 8
            RightRotate(D, x->parent);               // case 8
            x = D->root;
	 }
        }
   } 
                               // case 8
   x->color = BLACK; 
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
      exit(1);
   }
   if(D->size == 0){
	return(VAL_UNDEF);
   }
   Node N = treeSearch(D,D->root,k);
   if(N == D->NIL || N == NULL) {
       return VAL_UNDEF;
   }
   else{
	return(N->val);
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
   Y = D->NIL;
   X = D->root;
   Z = newNode(k,v);
   while(X != D->NIL){
	Y = X;
	if(KEY_CMP(Z->key,X->key) < 0){
		X = X->left;
	}
	else{
		X = X->right;
	}
   }
   Z->parent = Y;
   if(Y == D->NIL){
	D->root = Z;
   }
   else if(KEY_CMP(Z->key, Y->key) < 0){
	Y->left = Z;
   }
   else{
	Y->right = Z;
   }
   Z->left = D->NIL;
   Z->right = D->NIL;
   Z->color = RED;
   InsertFixUp(D,Z);
   D->size++;
}
// delete()
// Remove the pair whose key is k from Dictionary D.
// Pre: lookup(D,k)!=VAL_UNDEF (i.e. D contains a pair whose key is k.)
void delete(Dictionary D, KEY_TYPE k){
   if(D == NULL || (lookup(D,k) == VAL_UNDEF && treeSearch(D,D->root,k) == D->NIL)){
	return;
   }
   Node Z = treeSearch(D, D->root,k);
   Node Y = Z;
   Node X;
   int a;
   a = Y->color;

   if(Z == D->NIL){
	return;
   }
   if(Z->left == D->NIL){
	X = Z->right;
	Transplant(D, Z, Z->right);
   }
   else if(Z->right == D->NIL){
	X = Z->left;
	Transplant(D,Z,Z->left);
   }
   else{
	Y = treeMin(D,Z->right);
      	a = Y->color;
	X = Y->right;
	if(Y->parent != Z){
		Transplant(D,Y,Y->right);
		Y->right = Z->right;
		Y->right->parent = Y;
	}
	else{
		X->parent =  Y;
	}
	Transplant(D,Z,Y);
	Y->left = Z->left;
	Y->left->parent = Y;
	Y->color = Z->color;
   }
   if(a == BLACK){
	DeleteFixUp(D,X);
   }
   if(D->cursor == Z){
	D->cursor = D->NIL;
   }
   freeNode(&Z);
   D->size--;
}

// makeEmpty()
// Reset Dictionary D to the empty state, containing no pairs.
void makeEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, "Dictionary Error: makeEmpty() called on NULL Dictionary reference");
      exit(EXIT_FAILURE);
   }   
   emptyTree(D,D->root);
   D->root = D->NIL;
   D->size = 0;
   D->cursor = D->NIL;
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
   X = treeMin(D,D->root);
   D->cursor = X;
   if(X == D->NIL){
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
   X = treeMax(D,D->root);
   D->cursor = X;
   if(X == D->NIL){
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
   if(D->cursor == D->NIL){
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
   if(D->cursor == D->NIL){
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
   if(D->cursor == D->NIL){
   	return VAL_UNDEF;
   }
   D->cursor = treeSuccessor(D, D->cursor);
   if(D->cursor == D->NIL){
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
   if(D->cursor == D->NIL){
        return VAL_UNDEF;
   }
   D->cursor = treePred(D, D->cursor);
   if(D->cursor == D->NIL){
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

void printPost(FILE* out,Dictionary D, Node x){
   if(x == D->NIL){
	return;
   }
   printPost(out,D,x->left); 
   printPost(out,D,x->right); 
   fprintf(out, "%s", x->key);
}
void printIn(FILE* out,Dictionary D, Node x){
   if(x == D->NIL){
        return;
   }
   printIn(out,D,x->left);
   fprintf(out,"%s", x->key);
   printIn(out,D,x->right); 
}
void printPre(FILE* out,Dictionary D, Node x){
   if(x == D->NIL){
        return;
   }
   fprintf(out, "%s", x->key);
   printPre(out,D,x->left);
   printPre(out,D,x->right); 
}  

void printDictionary(FILE* out, Dictionary D, const char* ord){
   if(strcmp(ord,"pre") == 0){
	printPre(out, D, D->root);
   }
   else if(strcmp(ord,"in") == 0){
	printIn(out, D, D->root);
   }
   else if(strcmp(ord,"post") == 0){
	printPost(out, D, D->root);
   }
}
