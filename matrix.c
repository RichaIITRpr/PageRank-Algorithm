#include <stdio.h>
#include <stdlib.h>

#ifndef MATRIX_H
#define MATRIX_H

typedef struct Sparse_matrix* Sparse_matrix;
typedef struct node* node;

struct node{
	double val;
	int col;
	struct node* next;
};

struct Sparse_matrix{
	node values;
	int* row_index;
	int rows;
	int cols;
};

Sparse_matrix CSRMatrix(int rows, int cols){
	Sparse_matrix A = malloc(sizeof(*A));
	A->rows = rows;
	A->cols = cols;
	A->values = NULL;
	A->row_index = calloc(rows + 1, sizeof(int));
	return A;
}

node GetNode(double value, int col){
	node n = malloc(sizeof(*n));
	n->val = value;
	n->col = col;
	n->next = NULL;
	return n;
}

void DelList(node start){
	if(start == NULL)	return;
	node next = start->next;
	free(start);
	DelList(next);
}

void DelMx(Sparse_matrix A){
	DelList(A->values);
	free(A->row_index);
	free(A);
}

void AddValue(Sparse_matrix A, double val, int row, int col){
	int num_el = A->row_index[row+1] - A->row_index[row];
	node cur = A->values;
	node prev = cur;
	for(int i = 0; i < A->row_index[row]; i++){
		prev = cur;
		cur = cur->next;
	}
	for(int i = 0; i < num_el && cur->col < col; i++){
		prev = cur;
		cur = cur->next;
	}
	node n = GetNode(val, col);
	if(A->row_index[row] == 0){
		n->next = A->values;
		A->values = n;
	}
	else{
		prev->next = n;
		n->next = cur;
	}
	for(int i = row + 1; i <= A->rows; i++){
		A->row_index[i]++;
	}
}

void DelValue(Sparse_matrix A, int row, int col){
	node cur = A->values, prev = cur;
	
	for(int i = 0; i < A->row_index[row]; i++){
		prev = cur;
		cur = cur->next;
	}
	
	int count = 0, num_el = A->row_index[row+1] - A->row_index[row];
	
	for(int i = 0; i < num_el; i++){
		if(cur->col == col)	break;
		prev = cur;
		cur = cur->next;
	}
	
	if(prev != cur)	prev->next = cur->next;
	else			A->values = cur->next;

	free(cur);
	for(int i = row + 1; i <= A->rows; i++){
		A->row_index[i]--;
	}
}

void ChangeVal(Sparse_matrix A, int row, int col, double new_val){
	node cur = A->values, prev;
	for(int i = 0; i < A->row_index[row]; i++)	cur = cur->next;
	int count = 0, num_el = A->row_index[row+1] - A->row_index[row];
	for(int i = 0; i < num_el; i++){
		if(cur->col == col)	break;
		cur = cur->next;
	}
	cur->val = new_val;
}

Sparse_matrix DupMx(Sparse_matrix A){
	Sparse_matrix B = CSRMatrix(A->rows, A->cols);
	for(int i = 0; i <= A->rows; i++){
		B->row_index[i] = A->row_index[i];
	}
	node cur_A = A->values;
	if(cur_A != NULL){
		B->values = GetNode(cur_A->val, cur_A->col);
		cur_A = cur_A->next;
	}
	node cur_B = B->values;
	while(cur_A != NULL){
		cur_B->next = GetNode(cur_A->val, cur_A->col);
		cur_A = cur_A->next;
		cur_B = cur_B->next;
	}
	return B;
}

Sparse_matrix Normalize(Sparse_matrix A){
	node cur = A->values;
	for(int i = 0; i < A->rows; i++){
		int num_el = A->row_index[i+1] - A->row_index[i];

		if(num_el == 0)	continue;

		for(int count = 0; count < num_el; count++){
			cur->val /= num_el;
			cur = cur->next;
		}
	}
}

void PrintMx(Sparse_matrix M){
	int cols = M->cols, rows = M->rows;
	node cur = M->values;
	for(int i = 0; i < rows; i++){
		int num_el = M->row_index[i+1] - M->row_index[i];
		int num_pt = 0;
		for(int j = 0; j < cols; j++){
			if(cur != NULL && num_pt < num_el && cur->col == j){
				printf("%lf ", cur->val);
				cur = cur->next;
				num_pt++;
				continue;
			}
			printf("0 ");
		}
		printf("\n");
	}
}

#endif