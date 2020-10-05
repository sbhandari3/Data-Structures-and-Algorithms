/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA4
* FindComponents.c
* FindComponents is to test Graph.c for DFS
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
	int size, a, b, c, x,y;
	List li;
	Graph G, N;
	FILE* in; // file handle for input
 	FILE* out; // file handle for output

 	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open input file for reading
	in = fopen(argv[1], "r");
	if( in==NULL ){
		printf("Unable to read from file %s\n", argv[1]);
		exit(1);
	}

	// open output file for writing
	out = fopen(argv[2], "w");
	if( out==NULL ){
		printf("Unable to write to file %s\n", argv[2]);
		exit(1);
	}
	
fscanf(in, " %d", &size);
	G = newGraph(size);

	fscanf(in, " %d", &a);
	fscanf(in, " %d", &b);
	while(a != 0){
		if(b != 0){
			addArc(G, a, b);
			fscanf(in, " %d", &a);
			fscanf(in, " %d", &b);
		}
	}

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

	li = newList();
	for(y = 0; y < size; ++y){
		append(li, y + 1);
	}

	DFS(G, li);
	N = transpose(G);
	DFS(N, li);
	// components
	y = 0;
	
for(moveFront(li);index(li) != -1;moveNext(li)){
		if(getParent(N, get(li)) == NIL){
			++y;
		}
	}
	
	fprintf(out, "\nG contains %d strongly connected components:", y);
	// print 
	y = 0;
	moveBack(li);
	while(index(li) != -1){
		++y;
		fprintf(out, "\nComponent %d:", y);
		c = 0;
		while(1){
			if(index(li) == -1){
				moveFront(li);
				break;
			}
			++c;
			if(getParent(N, get(li)) == NIL){
				break;
			}
			movePrev(li);
		}
		fprintf(out, " %d", get(li));
		x = 0;
		while(x < c - 1){
			moveNext(li);
			fprintf(out, " %d", get(li));
			++x;
		}
		x = 0;
		while(x < c){
			movePrev(li);
			++x;
		}
	}
	fprintf(out, "\n");

	// free
	freeGraph(&G);
	freeGraph(&N);
	freeList(&li);
	fclose(in);
  	fclose(out);
	return(0);
}



