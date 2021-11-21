//to sort ranking
#include<stdio.h>
#include "graph.c"

void swapF(float* x, float* y){
	float temp = *x;
	*x= *y;
	*y = temp;
}

void swapI(int* x, int* y){
	int temp = *x;
	*x= *y;
	*y = temp;
}

int Rank(FILE* f, float* r, int size){
	float temp[size];
	int tmp_idx[size];

	//creating a temporary matrix, with index as column 2 elements.
	for(int i = 0; i < size; i++){
		temp[i] = r[i];
		tmp_idx[i] = i+1;
	}

	//to sort the column 0 in descending order
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size-i; j++){
			if(temp[j+1] > temp[j]){
				swapF(&temp[j], &temp[j+1]);
				swapI(&tmp_idx[j], &tmp_idx[j+1]);
			}
		}
	}

	//to print the temp matrix
	for(int i = 0; i < size; i++){
		fprintf(f, "%d (%f)\n", (int)tmp_idx[i], temp[i]);
	}

}

int main(){
	FILE* f_in = fopen("input.txt", "r");
	FILE* f_out = fopen("output.txt", "w");

	int v;
	char temp;

	fscanf(f_in, "%d%c", &v, &temp);

	graph g = GraphInit(v);

	while(1){
		int i, j;
		fscanf(f_in, "%d%d%c", &i, &j, &temp);
		if(i == -1)	break;
		AddEdge(g, i, j);
	}

	float* r = PageRank(g);
	Rank(f_out, r, v);
	fprintf(f_out, "\n");
	for(int i = 0; i < v; i++){
		fprintf(f_out, "%f ", r[i]);
	}
	fprintf(f_out, "\n");

	DelGraph(g);
}