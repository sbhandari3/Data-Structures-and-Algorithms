/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA2
* Arithmetic.c
* Arithmetic.c is to produce an output using BigInteger ADT
*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BigInteger.h"

int MAX = 100000000;

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	// char line[MAX];
	// char len_big_int_1[MAX];
	// char len_big_int_2[MAX];

	if (argc != 3) {
		printf("Usage: %s <input> <output>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	in = fopen(argv[1], "r");

	if (in == NULL) {
		printf("ERROR: unable to read input file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	out = fopen(argv[2], "w");

	if (out == NULL) {
		printf("ERROR: unable to read output file %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
}
