/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA3
* GraphTest.c
* GraphTest.c is a test client for Graph.c
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[])
{
	Graph A = newGraph(12);
	Graph B = newGraph(12);
	List list = newList();
	int k;

	for(k = 1; k < 11; k+=2){
			addEdge(B, k, k);
			addArc(A, k, k);
	}

	BFS(A, 6);
	BFS(B, 4);

	printf("%d\n", getOrder(A));
	printf("%d\n", getOrder(B));

	printf("%d\n", getSize(A));
	printf("%d\n", getSize(B));

	printf("%d\n", getSource(A));
	printf("%d\n", getSource(B));

	printf("%d\n", getParent(A, 1));
	printf("%d\n", getParent(B, 3));

	getPath(list, A, 2);
	getPath(list, B, 6);

	printList(stdout, list);

	printGraph(stdout, A);
	//printGraph(stdout, B);

	makeNull(B);
	printGraph(stdout, B);

	freeGraph(&A);
	freeGraph(&B);
	freeList(&list);
	return(0);
}
