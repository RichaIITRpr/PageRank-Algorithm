#include <stdio.h>
#include <stdlib.h>

#ifndef MATRIX_H
#define MATRIX_H

typedef struct Sparse_matrix* Sparse_matrix;
typedef struct node* node;

struct node{
	float val;
	int col;
	struct node* next;
};

//	Struct to implement Compressed Sparse Row (CSR) matrix
struct Sparse_matrix{
	node values;		//	Stores the non-zero values along with the column index to the value
	int* row_index;		//	i th index of the array stores the total non-zero element in the rows preceeding it
	int rows;			//	Number of rows in the matrix
	int cols;			//	Number of cols in the matrix
};

//	Intialize an empty matrix
Sparse_matrix CSRMatrix(int rows, int cols){
	Sparse_matrix A = malloc(sizeof(*A));
	A->rows = rows;
	A->cols = cols;
	A->values = NULL;
	A->row_index = calloc(rows + 1, sizeof(int));
	return A;
}

//	Returns a node with the value and col field filled with given arguments
node GetNode(float value, int col){
	node n = malloc(sizeof(*n));
	n->val = value;
	n->col = col;
	n->next = NULL;
	return n;
}

//	 Delete the list starting with the given node
void DelList(node start){
	if(start == NULL)	return;
	node next = start->next;
//	Free the current node
	free(start);
//	then delete the list starting at next node
	DelList(next);
}

//	Free up the space allocated to the matrix
void DelMx(Sparse_matrix A){
	DelList(A->values);
	free(A->row_index);
	free(A);
}

//	Add a non-zero element to the matrix
void AddValue(Sparse_matrix A, float val, int row, int col){
//	Loop to the correct place to insert the new non-zero element
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
//	Allocate new node and add it to the place
	node n = GetNode(val, col);
	if(A->values == NULL || cur == prev){
		n->next = A->values;
		A->values = n;
	}
	else{
		prev->next = n;
		n->next = cur;
	}
//	Update the row_index array after the new insertion
	for(int i = row + 1; i <= A->rows; i++){
		A->row_index[i]++;
	}
}

//	Delete a non-zero element i.e change it to zero
void DelValue(Sparse_matrix A, int row, int col){
	node cur = A->values, prev = cur;
//	Find the node that is used to represent this non-zero element
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

//	Free the node and adjust for the removal of a node from the list
	if(prev != cur)	prev->next = cur->next;
	else			A->values = cur->next;

	free(cur);

//	Update the row_index array to account for the removal of a non-zero element
	for(int i = row + 1; i <= A->rows; i++){
		A->row_index[i]--;
	}
}

//	To change the value of a non-zero element at the given location
void ChangeVal(Sparse_matrix A, int row, int col, float new_val){
	node cur = A->values, prev;
//	Find the element and change its value field
	for(int i = 0; i < A->row_index[row]; i++)	cur = cur->next;
	int count = 0, num_el = A->row_index[row+1] - A->row_index[row];
	for(int i = 0; i < num_el; i++){
		if(cur->col == col)	break;
		cur = cur->next;
	}
	cur->val = new_val;
}

//	Returns another matrix which is the same as the input matrix
Sparse_matrix DupMx(Sparse_matrix A){
//	First duplicate the structure
	Sparse_matrix B = CSRMatrix(A->rows, A->cols);
	for(int i = 0; i <= A->rows; i++){
		B->row_index[i] = A->row_index[i];
	}
//	Then copy the list of non-zero elements associated with the input matrix
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

//	Normalise each row of the input matrix
void Normalize(Sparse_matrix A){
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

//	Print the matrix to the output
void PrintMx(Sparse_matrix M, FILE* f_out){
	int cols = M->cols, rows = M->rows;
	node cur = M->values;
	for(int i = 0; i < rows; i++){
		int num_el = M->row_index[i+1] - M->row_index[i];
		int num_pt = 0;
		for(int j = 0; j < cols; j++){
			if(cur != NULL && num_pt < num_el && cur->col == j){
				fprintf(f_out, "%lf ", cur->val);
				cur = cur->next;
				num_pt++;
				continue;
			}
			fprintf(f_out, "0 ");
		}
		fprintf(f_out, "\n");
	}
}

#endif