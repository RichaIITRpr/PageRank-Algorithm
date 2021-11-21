//to sort ranking
#include<stdio.h>

#define MAX 100

void swap(int *x, int *y){
    int temp = *x;
    *x= *y;
    *y = temp;
}

int main(){
    int A[MAX];
    int arows;
    int i;

    printf("Enter number of rows: ");
    scanf("%d", &arows);

    printf("Enter the elements of the matrix: ");
    for(i=0; i<arows; i++){
        scanf("%d", &A[i]);
    }


    int temp[MAX][2];
    int temp_r;
    temp_r=arows;

    //creating a temporary matrix, with index as column 2 elements.
    for(int i=0; i<temp_r; i++){
        temp[i][1]=A[i];
        temp[i][0]=i+1;
    }

    // printf("\ntemp matrix: \n");
    // for(int i=0; i<arows; i++){
    //     for(int j=0; j<2; j++){
    //         printf("%d ", temp[i][j]);
    //     }
    //     printf("\n");
    // }

    
    //to sort the column1 in descending
    for(int i=0; i<arows-1; i++){
        for(int j=0; j<arows-1-i; j++ ){
            if(temp[j+1][1]>temp[j][1]){
            swap(&temp[j][0], &temp[j+1][0]);
            swap(&temp[j][1], &temp[j+1][1]);
            }
        }
    }

    //to print the temp matrix
    printf("\nRequired sorting. \n");
    printf("VERTEX\tVALUE\n");
    for(int i=0; i<temp_r; i++){
        for(int j=0; j<2; j++){
            printf("%d\t", temp[i][j]);
        }
        printf("\n");
    }

    return 0;
}