/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA2
* BigInteger.c
* BigInteger.c has methods for Arithmetic.c
*********************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BigInteger.h"
#include "List.h"

# define base 1000000000
# define pow 9

// structs --------------------------------------------------------------------

// private BigInteger
typedef struct BigIntegerObj
{
   	int posneg;
   	List intList;
}
BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

BigInteger newBigInteger()
{
	BigInteger A;
	A = malloc(sizeof(BigIntegerObj));
	A->posneg = 0;
	A->intList = newList();
	return(A);
}

void freeBigInteger(BigInteger* pN)
{
	if(pN!=NULL && *pN!=NULL)
   { 
      freeList(&(*pN)->intList);
      free(*pN);
      *pN = NULL;
   }
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
		exit(1);
	}
	return(N->posneg);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
	if(A == NULL){
		printf("BigInteger Error: calling equals() on NULL BigInteger reference\n");
		exit(1);
	}
	if(B == NULL){
		printf("BigInteger Error: calling equals() on NULL BigInteger reference\n");
		exit(1);
	}

	if(A==B){
		return(0);
	}
	if(A->posneg < B->posneg){
		return(-1);
	}
	if(length(A->intList) > length(B->intList)){
		return (1 * A->posneg);
	}
	if(A->posneg > B->posneg){
		return(1);
	}
	if(length(A->intList) < length(B->intList)){
		return(-1 * A->posneg);
	}
	
	
	moveBack(B->intList);
	
	for(moveBack(A->intList); index(A->intList) != -1; moveNext(A->intList)){
		if(get(A->intList) < get(B->intList)){
			return(-1 * A->posneg);
		}
		if(get(A->intList) > get(B->intList)){
			return(1 * A->posneg);
		}
		
		moveNext(B->intList);
	}
	return(0);
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
	if(A == NULL){
		printf("BigInteger Error: calling equals() on NULL BigInteger reference\n");
		exit(1);
	}
	if(B == NULL){
		printf("BigInteger Error: calling equals() on NULL BigInteger reference\n");
		exit(1);
	}

	if(compare(A, B) == 0){
		return(1);
	}
	return(0);
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
		exit(1);
	}
	N->posneg = 0;
	clear(N->intList);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N){
	if(N == NULL){
		printf("BigInteger Error: calling negate() on NULL BigInteger reference\n");
		exit(1);
	}
	N->posneg*= -1;
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten numbers {0,1,2,3,4,5,6,7,8,9}
// and an optional posneg {+, -} prefix.
BigInteger stringToBigInteger(char* s){
    int j;
    j = 0;
    int k;
    int negone = -1;
    long number;
    BigInteger A =newBigInteger();
    List list = newList();
    
  
    if(s == NULL){
	    printf("BigInteger Error: calling stringToBigInteger() on NULL char* reference\n");
	    exit(1);
    }
    if(s[0] == '-'){
        ++j;
        A->posneg = negone;
    }
    else{
        A->posneg = 1;
        if(s[0] == '+')
            ++j;
    }
    if(s[j] == '\0')
    {
        printf("BigInteger Error: string with only +/-\n");
        exit(1);
    }
 if(s[0] == '\0') {
        printf("BigInteger Error: empty string\n");
        exit(1);
    }

    
while(s[j] != '\0'){
        if(47 < s[j] && s[j] < 58) {
            append(list, s[j] - 48);
        }
        else {
            printf("BigInteger Error: invalid char in string\n");
            exit(1);
        }
        ++j;
    }
    moveFront(list);
    while(index(list) != negone && get(list) == 0){
    	delete(list);
    	moveFront(list);
    }
    if(index(list) != negone){
	    moveBack(list);
	    k = 1;
	    number = 0;
	    while(index(list) != negone){
	        number += k * get(list);
	        movePrev(list);
	 
	        if(k * 10 >= base || index(list) == negone){
	            append(A->intList, number);
	            number = 0;
	            k = 1;
	         }
	        else{
	            k*= 10;
	       }
	    }
	}
	else{
		A->posneg = 0;
	}
    freeList(&list);
    return(A);
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
	BigInteger A;
	if(N == NULL)
	{
		printf("BigInteger Error: calling copy() on NULL BigInteger reference\n");
		exit(1);
	}
	A = newBigInteger();
	// have to manually copy the List because of conflicting name Copy
	A->posneg = N->posneg;
	for(moveFront(N->intList); index(N->intList) != -1; moveNext(N->intList)){
		append(A->intList, get(N->intList));
	}
	return(A);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
	BigInteger C;
	if(S == NULL){
		printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
		exit(1);
	}
	if(A == NULL || B == NULL){
		printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
		exit(1);
	}

	C = sum(A, B);
	clear(S->intList);
	S->posneg = C->posneg;
	for(moveFront(C->intList); index(C->intList) != -1; moveNext(C->intList)){
		append(S->intList, get(C->intList));
	}
	freeBigInteger(&C);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
	long number,adder;
	int one = 1;
	int negone = -1;
	BigInteger C;
	if(A == NULL){
		printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
		exit(1);
	}
	if(B == NULL){
		printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
		exit(1);
	}

	if(A->posneg == 0)
	{
		C = copy(B);
		return(C);
	}
	if(B->posneg == 0)
	{
		C = copy(A);
		return(C);
	}
	if(A->posneg == negone && B->posneg == one)
	{
		A->posneg = one;
		C = diff(B, A);
		A->posneg = negone;
		return(C);
	}
	if(A->posneg == one && B->posneg == negone)
	{
		B->posneg = one;
		C = diff(A, B);
		B->posneg = negone;
		return(C);
	}
	C = newBigInteger();
	C->posneg = A->posneg;

	adder = 0;
	
for(moveFront(A->intList), moveFront(B->intList); index(A->intList) != negone && index(B->intList) != negone;moveNext(A->intList),moveNext(B->intList)){
		number = get(A->intList) + get(B->intList) + adder;
		adder = floor(number / base);
		number = number % base;
		append(C->intList, number);
		
	}
	while(index(A->intList) != negone){
	//for(A->intList->cursor->data; index(A->intList) != negone; moveNext(A->intList)){
		number = get(A->intList) + adder;
		adder = floor(number / base);
		number = number % base;
		append(C->intList, number);
		moveNext(A->intList);
	}
	while(index(B->intList) != negone){
	//for(B->intList->cursor->data; index(B->intList) != negone; moveNext(B->intList)){
		

number = get(B->intList) + adder;
		adder = floor(number / base);
		number = number % base;
		append(C->intList, number);
		moveNext(B->intList);
	}
	
// x
// y
if(adder != 0){
		append(C->intList, adder);
	}
	return(C);
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B){
	BigInteger C;
	if(D == NULL){
		printf("BigInteger Error: calling subtract() on NULL BigInteger reference\n");
		exit(1);
	}
	if(A == NULL || B == NULL){
		printf("BigInteger Error: calling subtract() on NULL BigInteger reference\n");
		exit(1);
	}

	C = diff(A, B);
	clear(D->intList);
	D->posneg = C->posneg;

	for(moveFront(C->intList); index(C->intList) != -1; moveNext(C->intList)){
		append(D->intList, get(C->intList));
		
	}
	freeBigInteger(&C);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
	long number;
	long adder;
	int negone = -1;
	BigInteger N;
	BigInteger first, last;
	if(A == NULL || B == NULL){
		printf("BigInteger Error: calling diff() on NULL BigInteger reference\n");
		exit(1);
	}
	if(A->posneg == 0){
		N = copy(B);
		return(N);
	}
	if(B->posneg == 0){
		N = copy(A);
		negate(N);
		return(N);
	}
	if(A->posneg == -1 && B->posneg == 1){
		B->posneg = -1;
		N = sum(A, B);
		B->posneg = 1;
		return(N);
	}
	if(A->posneg == 1 && B->posneg == -1){
		B->posneg = 1;
		N = sum(A, B);
		B->posneg = -1;
		return(N);
	}
	if(equals(A, B) == 1){
		return(newBigInteger());
	}

	N = newBigInteger();
	if((compare(A, B)==1 && A->posneg==1) || (compare(A, B)==-1 && A->posneg==-1)){
		first = A;
		last = B;
		N->posneg = A->posneg;
	}
	else{
		first = B;
		last = A;
		N->posneg = A->posneg * -1;
	}
	
	adder = 0;

	for(moveFront(first->intList), moveFront(last->intList); index(first->intList) != negone && index(last->intList) != negone;moveNext(first->intList),moveNext(last->intList)){
		number = get(first->intList) - get(last->intList) + adder;
		if(number < 0){
			number+= base;
			adder = -1;
		}
		else{
			adder = 0;
		append(N->intList, number);
		}
	}
	while(index(first->intList) != -1){
		number = get(first->intList) + adder;
		if(number < 0){
			number+= base;
			adder = -1;
		}
		else{
			adder = 0;
		append(N->intList, number);
		moveNext(first->intList);
		}
	}
	
	return(N);
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
	BigInteger C;
	if(P == NULL){
		printf("BigInteger Error: calling multiply() on NULL BigInteger reference\n");
		exit(1);
	}
	if(A == NULL || B == NULL){
		printf("BigInteger Error: calling multiply() on NULL BigInteger reference\n");
		exit(1);
	}

	C = prod(A, B);
	clear(P->intList);
	P->posneg = C->posneg;

	for(moveFront(C->intList); index(C->intList) != -1; moveNext(C->intList)){
		append(P->intList, get(C->intList));
	
	}
	freeBigInteger(&C);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B){
	int x, y, big, i;
	long adder, number;
	long* arr;
	BigInteger N;
	if(A == NULL){
		printf("BigInteger Error: calling prod() on NULL BigInteger reference\n");
		exit(1);
	}
	if(B == NULL){
		printf("BigInteger Error: calling prod() on NULL BigInteger reference\n");
		exit(1);
	}

	N = newBigInteger();
	
	if(A->posneg == 0 || B->posneg == 0)
		return(N);
	if(A->posneg == B->posneg){
		N->posneg = 1;
	}
	else{
		N->posneg = -1;
	}

	x = 0;
	big = -1 + length(A->intList) + length(B->intList);
	arr = calloc(sizeof(long), big);

	for(moveFront(A->intList); index(A->intList) != -1;moveNext(A->intList)){
		y = 0;
		for(moveFront(B->intList); index(B->intList) != -1;moveNext(B->intList)){
			arr[x + y]+= get(A->intList) * get(B->intList);
			//moveNext(B->intList);
			++y;
		}
		++x;
	}
	adder = 0;
	for(i = 0; i<big; ++i){
		number = arr[i] + adder;
		adder = floor(number / base);
		number = number % base;
		append(N->intList, number);
	}
	
	while(adder != 0){
		append(N->intList, adder % base);
		adder = floor(adder / base);
	}
	free(arr);
	return(N);
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
	int j;
	if(N == NULL){
		printf("BigInteger Error: calling printBigInteger() on NULL BigInteger reference\n");
		exit(1);
	}
	if(N->posneg == 0)
		fprintf(out, "0\n");
	else{
		if(N->posneg == -1)
			fprintf(out, "-");
		moveBack(N->intList);
		fprintf(out, "%ld", get(N->intList));
		for(movePrev(N->intList); index(N->intList) != -1; movePrev(N->intList)){
			if(get(N->intList) < 0){
				printf("BigInteger Error: overflow occurred: \n");
				exit(1);
			}
			if(get(N->intList) == 0){
				for(j=0; j<pow - 1; j++){
					fprintf(out, "0");
				}
			}
			else{
				for(j=10; base > get(N->intList) * j; j*= 10){
					fprintf(out, "0");
				}
			}
			fprintf(out, "%ld", get(N->intList));
		}
		fprintf(out, "\n");
	}
}




