/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA2
* BigIntegerTest.c
* Test file for BigInteger.c
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include "BigInteger.h"


int main(int argc, char* argv[])
{
	BigInteger A, B, C, D, E, F, G;

	A = stringToBigInteger("123489");
	B = stringToBigInteger("-21");
	C = stringToBigInteger("-0");
	D = stringToBigInteger("+0");
	//E = stringToBigInteger("+1234");
	//F = stringToBigInteger("-000543210");
	//G = stringToBigInteger("1234");

	printf("print tests:\n");
	printBigInteger(stdout, A);
	printBigInteger(stdout, B);
	//printBigInteger(stdout, C);
	//rintBigInteger(stdout, D);
	printBigInteger(stdout, E);
	printBigInteger(stdout, F);
	printBigInteger(stdout, G);

	printf("\ncompare tests:\n");
	printf("%d\n", compare(E, G));
	printf("%d\n", compare(C, D));
	printf("%d\n", compare(A, B));
	//printf("%d\n", compare(E, F));
	printf("%d\n", compare(F, E));

	printf("\ncopy tests:\n");
	freeBigInteger(&C);
	freeBigInteger(&D);
	C = copy(A);
	//D = copy(B);
	printBigInteger(stdout, C);
	printBigInteger(stdout, D);

	printf("\nadd and sum tests:\n");
	freeBigInteger(&C);
	C = sum(A, E);
	add(D, B, F);
	printBigInteger(stdout, C);
	//printBigInteger(stdout, D);
	freeBigInteger(&C);
	C = sum(A, B);
	add(D, F, E);
	//printBigInteger(stdout, C);
	printBigInteger(stdout, D);

	printf("\nsubtract and diff tests:\n");
	freeBigInteger(&C);
	C = diff(A, E);
	subtract(D, B, F);
	printBigInteger(stdout, C);
	printBigInteger(stdout, D);
	freeBigInteger(&C);
	C = diff(A, B);
	subtract(D, F, E);
	printBigInteger(stdout, C);
	printBigInteger(stdout, D);

	printf("\nmultiply and prod tests:\n");
	freeBigInteger(&C);
	C = prod(A, E);
	multiply(D, B, F);
	//printBigInteger(stdout, C);
	//printBigInteger(stdout, D);
	freeBigInteger(&C);
	C = prod(A, B);
	//multiply(D, F, E);
	printBigInteger(stdout, C);
	printBigInteger(stdout, D);

	freeBigInteger(&A);
	freeBigInteger(&B);
	freeBigInteger(&C);
	freeBigInteger(&D);
	freeBigInteger(&E);
	freeBigInteger(&F);
	freeBigInteger(&G);

	return(0);
}
