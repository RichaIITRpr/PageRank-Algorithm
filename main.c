//to sort ranking
#include<stdio.h>
#include "graph.c"

//	Swap 2 floating point decimals
void swapF(float* x, float* y){
	float temp = *x;
	*x= *y;
	*y = temp;
}

//	Swap 2 integers
void swapI(int* x, int* y){
	int temp = *x;
	*x= *y;
	*y = temp;
}

//	Take in the output of PageRank and display the Ranking of vertices
int Rank(FILE* f, float* r, int size){
	float temp[size];
	int tmp_idx[size];

//	Creating a temporary matrix, with index as column 2 elements.
	for(int i = 0; i < size; i++){
		temp[i] = r[i];
		tmp_idx[i] = i+1;
	}

//	To sort the column 0 in descending order
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size-i; j++){
			if(temp[j+1] > temp[j]){
				swapF(&temp[j], &temp[j+1]);
				swapI(&tmp_idx[j], &tmp_idx[j+1]);
			}
		}
	}

//	To print the temp matrix
	for(int i = 0; i < size; i++){
		fprintf(f, "%d (%f)\n", (int)tmp_idx[i], temp[i]);
	}

}

int main(){
//	Open the input and output files
	FILE* f_in = fopen("input.txt", "r");
	FILE* f_out = fopen("output.txt", "w");

	int v;
	char temp;

//	Take in an integer which will be the number of vertices our graph will have
	fscanf(f_in, "%d%c", &v, &temp);

//	Initialise a graph with 0 edges
	graph g = GraphInit(v);

//	Loop through and take the edge inputs for the graph
	while(1){
		int i, j;
		fscanf(f_in, "%d%d%c", &i, &j, &temp);
	//	(-1 -1) to stop the loop
		if(i == -1)	break;
	//	Add the input edge to the graph
		AddEdge(g, i, j);
	}

//	Apply PageRank Algorithm get importance of each vertex
	float* r = PageRank(g);
//	Rank the vertices according to importance
	Rank(f_out, r, v);
//	Output the ranking of vertices
	fprintf(f_out, "\n");
	for(int i = 0; i < v; i++){
		fprintf(f_out, "%f ", r[i]);
	}
	fprintf(f_out, "\n");

//	Remove the graph and free up memory before exiting the program
	DelGraph(g);
	fclose(f_in);
	fclose(f_out);
}