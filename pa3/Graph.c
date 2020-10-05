/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA3
* Graph.c
* Graph.c is used for BF search
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"
#define NIL 0
#define INF -1


// structs --------------------------------------------------------------------


typedef struct GraphObj{
	List* list;
	int length;
	int source;
	int order;
	int size;
	int* color;
	int* parent;
	int* distance;
}
GraphObj;


// Constructors-Destructors ---------------------------------------------------

// Returns a reference to a new Graph object with n vertices and 0 edges.
Graph newGraph(int n){
	int i;
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->list = malloc(sizeof(List) * n);
	G->parent = malloc(sizeof(int) * n);
	G->distance = malloc(sizeof(int) * n);
	G->color = malloc(sizeof(int) * n);
	for(i = 0; i < n; ++i)
	{
		G->list[i] = newList();
		G->parent[i] = G->distance[i] = -1;
	}
	G->length = n;
	G->size = 0;
	G->source = -1;
	G->order = -1;
	return(G);
}

// Frees all heap memory associated with Graph *pG, and sets *pG to NULL
void freeGraph(Graph* pG){
	int i;
	if(pG != NULL && *pG != NULL){ 
		for(i = 0; i < (*pG)->length; ++i){
			freeList(&(*pG)->list[i]);
		}
		free((*pG)->list);
		free((*pG)->parent);
		free((*pG)->distance);
		free((*pG)->color);
		free(*pG);
		*pG = NULL;
	}
}


// Access functions -----------------------------------------------------------

// returns the order of G or NIL if BFS hasn't been run yet
int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: getOrder called with NULL Graph reference");
		exit(1);
	}
	return(G->order);
}

// returns number of vertices
int getSize(Graph G){
	if(G == NULL){
		printf("Graph Error: getSize called with NULL Graph reference");
		exit(1);
	}
	return(G->size);
}

// returns the most recent source used in BFS or NIL if BFS hasn't been run
int getSource(Graph G){
	if(G == NULL){
		printf("Graph Error: getSource called with NULL Graph reference");
		exit(1);
	}
	if(G->source == -1){
		return(NIL);
	}
	else{
		return(G->source);
	}
}

int getParent(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getParent called with NULL Graph reference");
		exit(1);
	}
	if(G->parent[u - 1] == -1){
		return(NIL);
	}
	else{
		return(1 + G->parent[u - 1]);
	}
}

int getDist(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getDist called with NULL Graph reference");
		exit(1);
	}
	if(G->distance[u - 1] == -1){
		return(INF);
	}
	return(G->distance[u - 1]);
}

// makes L list the path from the source to u
void getPath(List L, Graph G, int u){
	List A;
	A = newList();
	if(G == NULL || L == NULL){
		printf("Graph Error: getPath called with NULL reference");
		exit(1);
	}
	if(u > G->length){
		printf("Graph Error: getPath called with invalid u");
		exit(1);
	}
	
	u--;
	while(u != G->source - 1){
		if(u < 0){
			clear(A);
			break;
		}
		prepend(A, u + 1);
		u = G->parent[u];
	}
	if(u >= 0){
		prepend(A, u + 1);
		while(length(A) != 0){
			append(L, front(A));
			deleteFront(A);
		}
	}
	else{
		append(L, NIL);
	}
	freeList(&A);
}


// Manipulation procedures ----------------------------------------------------

// removes all edges from Graph G
void makeNull(Graph G)
{
	int i;
	i = 0;
	if(G == NULL){
		printf("Graph Error: makeNull called with NULL Graph reference");
		exit(1);
	}
	while( i < G->length){
		clear(G->list[i]);
 		i++;
	}
}

// makes an undirected edge from vertex u to vertex v
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: addEdge called with NULL Graph reference");
		exit(1);
	}
	if(u < 1 || v < 1){
		printf("Graph Error: addEdge called with invalid vertex");
		exit(1);
	}
	if(u > G->length || v > G->length){
		printf("Graph Error: addEdge called with invalid vertex");
		exit(1);
	}
	if(u != v){
		addArc(G, u, v);
		addArc(G, v, u);
		G->size--;
	}
}

// makes a directed edge from vertex u to vertex v
void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: addArc called with NULL Graph reference");
		exit(1);
	}
	if(u < 1 || v < 1){
		printf("Graph Error: addArc called with invalid u/v");
		exit(1);
	}
	if(u > G->length || v > G->length){
		printf("Graph Error: addArc called with invalid u/v");
		exit(1);
	}

	if(u != v){
		for(moveFront(G->list[u - 1]);index(G->list[u - 1]) != -1 && get(G->list[u - 1]) < v - 1;moveNext(G->list[u - 1])){
}
		if(index(G->list[u - 1]) == -1){
			append(G->list[u - 1], v - 1);
		}
		else{
			insertBefore(G->list[u - 1], v - 1);
		}
		G->size++;
	}
}

// sets source, order, parent*, and distance*
void BFS(Graph G, int s){
	int j, a, b;
	j = 0;
	List A;
	if(G == NULL){
		printf("Graph Error: BFS called with NULL Graph reference");
		exit(1);
	}
	if(s < 1){
		printf("Graph Error: BFS called with invalid s");
		exit(1);
	}
	if(G->length < s){
		printf("Graph Error: BFS called with invalid s");
		exit(1);
	}
	G->source = s;
	--s;
	//for(i = 0; i < G->length; ++i){
	while(j < G->length){
		G->parent[j] = G->distance[j] = -1;
		j++;
	}
	G->order = 1;
	G->distance[s] = 0;
	A = newList();
	append(A, s);
	while(length(A) != 0){
		a = front(A);
		deleteFront(A);
		//moveFront(G->list[a]);
		//while(index(G->list[a]) != -1){
		for(moveFront(G->list[a]);index(G->list[a]) != -1;moveNext(G->list[a])){
			b = get(G->list[a]);
			if(G->distance[b] == -1){
				G->distance[b] = G->distance[a] + 1;
				G->parent[b] = a;
				append(A, b);
				if(G->distance[b] > G->order + 1)
					G->order = G->distance[b] + 1;
			}
			//moveNext(G->list[a]);
		}
	}
	freeList(&A);
}


// Other operations ----------------------------------------------------

void printGraph(FILE* out, Graph G){
	int i;
	if(G == NULL){
		printf("Graph Error: printGraph called with NULL Graph reference");
		exit(1);
	}
	for(i = 0; i < G->length; ++i){
		fprintf(out, "%d:", i + 1);
		for(moveFront(G->list[i]); index(G->list[i]) != -1; moveNext(G->list[i])){
			fprintf(out, " %d", get(G->list[i]) + 1);
		}
		fprintf(out, "\n");
	}
}


