#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

#ifndef GRAPH_H
#define GRAPH_H

#define error 0.005

struct graph{
	int vertices;
	Sparse_matrix adj_matrix;
};

typedef struct graph* graph;

graph GraphInit(int v){
	graph g = malloc(sizeof(*g));
	g->vertices = v;
	g->adj_matrix = CSRMatrix(v, v);
	return g;
}

void DelGraph(graph g){
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

float MOD(float a){
	if(a < 0)	return (-1.0)*(a);
	return a;
}

char isEqual(float* r1, float* r2, int size){
	for(int i = 0; i < size; i++){
		if(MOD(r1[i] - r2[i]) >= error)	return 0;
	}
	return 1;
}

float* PageRank(graph g){
	float* r = calloc(g->vertices, sizeof(float));
	float* r_new;
	float* temp = calloc(g->vertices, sizeof(float));
	Sparse_matrix M = DupMx(g->adj_matrix);
	Normalize(M);
	node cur;

	for(int i = 0; i < g->vertices; i++)	r[i] = 1.0/(g->vertices);

	iteration:

	if(isEqual(r, temp, g->vertices)){
		free(temp);
		return r;
	}
	free(temp);
	cur = M->values;
	r_new = calloc(g->vertices, sizeof(float));

	for(int u = 0; u < M->rows; u++){
		int num_el = M->row_index[u + 1] - M->row_index[u];

		if(num_el == 0)	continue;

		for(int i = 0; i < num_el; i++){
			r_new[cur->col] += (float)r[u]*(float)(cur->val);
			cur = cur->next;
		}
	}
	temp = r;
	r = r_new;
	goto iteration;
}

#endif