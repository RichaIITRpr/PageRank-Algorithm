#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

#ifndef GRAPH_H
#define GRAPH_H

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
	AddValue(g->adj_matrix, 1, v, u);
}

//	Remove the edge from vertexx u to vertex v
void RemoveEdge(graph g, int u, int v){
	DelValue(g->adj_matrix, v, u);
}

double* PageRank(graph g){
	double* r = calloc(g->vertices, sizeof(double));
	double* r_new = calloc(g->vertices, sizeof(double));
	Sparse_matrix M = DupMx(g->adj_matrix);
	Normalize(M);
	node cur = M->values;

	for(int i = 0; i < g->vertices; i++)	r[i] = 1.0/(g->vertices);

	interation:

	for(int u = 0; u < M->rows; u++){
		int num_el = M->row_index[u + 1] - M->row_index[u];

		if(num_el == 0)	continue;

		for(int i = 0; i < num_el; i++){
			r_new[cur->col] += (cur->val)*r[cur->col];
			cur = cur->next;
		}

		double* temp = r;
		r = r_new;
		r_new = temp;

		goto interation;
	}
}

#endif