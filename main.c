//to sort ranking
#include<stdio.h>
#include "graph.c"

void swap(float* x, float* y){
	float temp = *x;
	*x= *y;
	*y = temp;
}

int Rank(FILE* f, float* r, int size){
	float temp[size][2];

	//creating a temporary matrix, with index as column 2 elements.
	for(int i = 0; i < size; i++){
		temp[i][0] = r[i];
		temp[i][1] = i+1;
	}

	
	//to sort the column 0 in descending order
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size-i; j++){
			if(temp[j+1][0] > temp[j][0]){
				swap(&temp[j][0], &temp[j+1][0]);
				swap(&temp[j][1], &temp[j+1][1]);
			}
		}
	}

	//to print the temp matrix
	for(int i = 0; i < size; i++){
		fprintf(f, "%d (%f)\n", (int)temp[i][1], temp[i][0]);
	}

}

int main(){
	FILE* f_in = fopen("input.txt", "r");
	FILE* f_out = fopen("output.txt", "w");

	FILE* temp_in = stdin;
	FILE* temp_out = stdout;

	stdin = f_in;
	stdout = f_out;

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

	stdin = temp_in;
	stdout = temp_out;
}