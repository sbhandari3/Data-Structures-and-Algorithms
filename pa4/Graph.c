/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA4
* Graph.c
* Graph.c is used for DF search
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"
#define NIL -1
#define UNDEF -2


// structs --------------------------------------------------------------------


typedef struct GraphObj{
	List* list;
	int length;
	int order;
	int size;
	int* disc;
	int* parent;
	int* fin;
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
	G->disc = malloc(sizeof(int) * n);
	G->fin = malloc(sizeof(int) * n);
	for(i = 0; i < n; ++i)
	{
		G->list[i] = newList();
		G->parent[i] = NIL;
		G->disc[i] = G->fin[i] = UNDEF;

	}
	G->length = n;
	G->size = 0;
	G->order = NIL;
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
		free((*pG)->disc);
		free((*pG)->fin);
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
/*int getSource(Graph G){
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
*/
int getParent(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getParent called with NULL Graph reference");
		exit(1);
	}
	if(G->parent[u - 1] == NIL){
		return(NIL);
	}
	else{
		return(1 + G->parent[u - 1]);
	}
}

int getDiscover(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getDiscover called with NULL Graph reference");
		exit(1);
	}
	return(G->disc[u - 1]);
}

// returns the finish time of vertex u
int getFinish(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getFinish called with NULL Graph reference");
		exit(1);
	}
	return(G->fin[u - 1]);
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
	--u;
	--v;
	if(G == NULL){
		printf("Graph Error: addArc called with NULL Graph reference");
		exit(1);
	}
	if(u < 0 || v < 0){
		printf("Graph Error: addArc called with invalid u/v");
		exit(1);
	}
	if(u >= G->length || v >= G->length){
		printf("Graph Error: addArc called with invalid u/v");
		exit(1);
	}

	if(1){
		for(moveFront(G->list[u]);index(G->list[u]) != -1 && get(G->list[u]) < v;moveNext(G->list[u])){
}
		if(index(G->list[u]) == -1){
			append(G->list[u], v);
		}
		else{
			insertBefore(G->list[u], v);
		}
		G->size++;
	}
}

// sets source, order, parent*, and distance*
/*void BFS(Graph G, int s){
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
*/

void visit(Graph G, int x, int* time, List S)
{
	G->disc[x] = ++(*time);
	for(moveFront(G->list[x]);index(G->list[x]) != -1;moveNext(G->list[x])){
		if(G->disc[get(G->list[x])] == UNDEF){
			G->parent[get(G->list[x])] = x;
			visit(G, get(G->list[x]), time, S);
		}
	}
	G->fin[x] = ++(*time);
	prepend(S, x + 1);
}

// sets order, parent, disc, and fin
void DFS(Graph G, List S){
	int i;
	int*t;
	List graph;
	if(G == NULL){
		printf("Graph Error: DFS called with NULL Graph reference");
		exit(1);
	}
	if(G->length != length(S)){
		printf("Graph Error: DFS called with incorrectly sized S");
		exit(1);
	}
	i =0;
	while(i < G->length){
		G->parent[i] = NIL;
		G->disc[i] = UNDEF;
		++i;
	}
	t = calloc(sizeof(int), 1);
	graph = copyList(S);
	clear(S);
	for(moveFront(graph);index(graph) != -1;moveNext(graph)){
		if(G->disc[get(graph) - 1] == UNDEF)
		{
			visit(G, get(graph) - 1, t, S);
		}
	}
	free(t);
	freeList(&graph);
}


// Other operations ----------------------------------------------------

// returns a transpose of G
Graph transpose(Graph G)
{
	int i;
	Graph graph;
	if(G == NULL){
		printf("Graph Error: transpose called with NULL Graph reference");
		exit(1);
	}
	graph = newGraph(G->length);
	i = 0;
	while(i < G->length){
		for(moveFront(G->list[i]);index(G->list[i]) != -1;moveNext(G->list[i])){
			addArc(graph, get(G->list[i]) + 1, i + 1);
		}
		++i;
	}
	graph->size = G->size;
	return(graph);
}

Graph copyGraph(Graph G)
{
	int j;
	Graph graph;
	if(G == NULL)
	{
		printf("Graph Error: copyGraph called with NULL Graph reference");
		exit(1);
	}
	graph = newGraph(G->length);
	j = 0; 
	while(j < G->length){
		freeList(&graph->list[j]);
		graph->list[j] = copyList(G->list[j]);
		graph->parent[j] = G->parent[j];
		graph->disc[j] = G->disc[j];
		graph->fin[j] = G->fin[j];
		++j;
	}
	graph->size = G->size;
	graph->order = G->order;
	return(graph);
}


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




