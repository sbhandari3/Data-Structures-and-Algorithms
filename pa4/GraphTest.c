/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA4
* GraphTest.c
* Tests for Graph.c
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
	Graph A = newGraph(5);
	Graph B = newGraph(10);
	List li = newList();
	int x, y;

	for(x = 1; x < 6; ++x){
		append(li, x);
	}

	for(x = 1; x < 6; x+=2)
	{
		for(y = 4; y < 8; ++y)
		{
			addEdge(B, x, y);
			addArc(A, x, y);
		}
	}

	DFS(A, li);
	DFS(B, li);

	printf("%d\n", getOrder(A));
	printf("%d\n", getSize(A));
	printf("%d\n", getParent(A, 3));
	printf("%d\n", getDiscover(A, 3));
	printf("%d\n", getFinish(A, 3));
	printGraph(stdout, A);


	freeGraph(&A);
	freeGraph(&B);
	freeList(&li);
	return(0);
}



