#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

#ifndef GRAPH_H
#define GRAPH_H

//	Define the margin of error for the obtained rank vector
#define error 0.005

//	For this case we use the adjacency matrix representation of the graph
/*
	In adjacency matrix A. The element A[i][j] is 1 if there exists
	an edge from i to j. In other  cases A[i][j] = 0.
*/
struct graph{
	int vertices;
	Sparse_matrix adj_matrix;
};

typedef struct graph* graph;

//	Initialize a graph with given number of vertices
graph GraphInit(int v){
//	Allocate memory for the struct
	graph g = malloc(sizeof(*g));
	g->vertices = v;
//	Initialize the adjacency matrix for the graph
	g->adj_matrix = CSRMatrix(v, v);
	return g;
}

//	Free the memory allocated for the graph struct
void DelGraph(graph g){
//	Free the matrix first
	DelMx(g->adj_matrix);
	free(g);
}

//	Adds an edge from vertex u to vertex v
void AddEdge(graph g, int u, int v){
	AddValue(g->adj_matrix, 1, u, v);
}

//	Remove the edge from vertexx u to vertex v
void RemoveEdge(graph g, int u, int v){
	DelValue(g->adj_matrix, u, v);
}

//	Modulus function implemented
float MOD(float a){
	if(a < 0)	return (-1.0)*(a);
	return a;
}

//	Determine whether the arrays r1 and r2 are close enough to be considered almost equal
char isEqual(float* r1, float* r2, int size){
	for(int i = 0; i < size; i++){
		if(MOD(r1[i] - r2[i]) >= error)	return 0;
	}
	return 1;
}

/*
	Takes in a graph and outputs a vector r whose i th element shows the importance of the i th vertex.
	The importance is calculated by taking into account the number of inward links to the vertex and the importance
	of the vertex from which the link is coming.
*/
float* PageRank(graph g){
//	To be initialised to an initial value
	float* r = calloc(g->vertices, sizeof(float));
//	Used to store the product
	float* r_new;
//	Initialise so that can be freed later on
	float* temp = calloc(g->vertices, sizeof(float));
//	Copy the adj_matrix of the graph into another matrix so that it can be normalized without affecting the graph
	Sparse_matrix M = DupMx(g->adj_matrix);
	Normalize(M);
	node cur;

//	Fill in the intial values
	for(int i = 0; i < g->vertices; i++)	r[i] = 1.0/(g->vertices);

//	Label to jump to at the end of iteration
	iteration:
//	Condition for iteration
	if(isEqual(r, temp, g->vertices)){
		free(temp);
		DelMx(M);
		return r;
	}
	free(temp);
	cur = M->values;
//	Allocate memory to store the multiplied values
	r_new = calloc(g->vertices, sizeof(float));

//	Loop through the rows
	for(int u = 0; u < M->rows; u++){
		int num_el = M->row_index[u + 1] - M->row_index[u];

		if(num_el == 0)	continue;

	//	Loop through the non-zero elements in the row u
		for(int i = 0; i < num_el; i++){
			r_new[cur->col] += (float)r[u]*(float)(cur->val);
			cur = cur->next;
		}
	}
//	Change temp to r, r to r_new
	temp = r;
	r = r_new;
//	Jump to the start of the iteration
	goto iteration;
}

#endif