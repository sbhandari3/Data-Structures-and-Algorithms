/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA3
* FindPath.c
* FindPath.c performs BFS using Graph.c
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
	int line, a, b;
	List srce, place, way;
	Graph FP;
	FILE* in,*out;

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

	// scan Graph size
	fscanf(in, " %d", &line);

	
	FP = newGraph(line);

	fscanf(in, " %d", &a);
	fscanf(in, " %d", &b);
	while(a != 0){
		if(b !=0){
			addEdge(FP, a, b);
			fscanf(in, " %d", &a);
			fscanf(in, " %d", &b);
		}
	}
	srce = newList();
	place = newList();
	way = newList();
	fscanf(in, " %d", &a);
	fscanf(in, " %d", &b);
	while(a != 0){
		if(b !=0){
			append(srce, a);
			append(place, b);
			fscanf(in, " %d", &a);
			fscanf(in, " %d", &b);
		}
	}
	printGraph(out, FP);
	
	while(length(srce) != 0){
		fprintf(out, "\n");
		a = front(srce);
		deleteFront(srce);
		b = front(place);
		deleteFront(place);
		BFS(FP, a);
		clear(way);
		getPath(way, FP, b);
		if(front(way) == NIL){
			fprintf(out, "The distance from %d to %d is infinity\n", a, b);
			fprintf(out, "No %d-%d path exists\n", a, b);
		}
		else{
			fprintf(out, "The distance from %d to %d is %d\n", a, b, getDist(FP, b));
			fprintf(out, "A shortest %d-%d path is: ", a, b);
			printList(out, way);
			fprintf(out, "\n");
		}
	}

	// free Graph and Lists
	freeGraph(&FP);
	freeList(&srce);
	freeList(&place);
	freeList(&way);

	// close files
	fclose(in);
  	fclose(out);

	return(0);
}


