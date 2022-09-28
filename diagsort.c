#include <stdio.h>
#include <stdlib.h>
/*
Description: Taking a matrix and sort all the elements on it's diagonals. 
(Problem #1329 of LeetCode)
Author: ScierKnave 
Language: C
*/


void diagQuickSort(int** mat, int i, int j, int length)
{
    if (length < 2){
        return;
    }
    int pivot = mat[i][j]; int temp;
    int a = 0; int b = length-1;

    while (a < b) {
        while(a < length -1 && mat[i+a][j+a] <= pivot){
            a++;
        }
        while(mat[i+b][j+b] > pivot){
            b--;
        }
        if (a < b) {
            temp = mat[i+a][j+a]; 
            mat[i+a][j+a] = mat[i+b][j+b];
            mat[i+b][j+b] = temp;
        }
    }
    if (mat[i+a][j+a] > pivot){
        a--;
    }
    temp = mat[i+a][j+a]; 
    mat[i+a][j+a] = mat[i][j];
    mat[i][j] = temp;
    diagQuickSort(mat, i, j, a); 
    diagQuickSort(mat, i+a+1, j+a+1, length-a-1);
}




//create a copy of mat were all the elements on it's diagonal are sorted
//here, the arguments are generic and not necessary optimized for the problem
int** diagonalSort(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes){
    int m = matSize; int n =  matColSize[0]; 
    int length;

    *returnSize = m;
    //set sizes of columns of returned matrix
    *returnColumnSizes = malloc(sizeof(int)*m);
    for (int i = 0; i < m; i++) (*returnColumnSizes)[i] = n;
    
    //call diagQuickSort on all the starting elements of the diagonals
    for (int d = 0; d < m + n -1; d++){
        if (d < m){
            length = (m-d > n) ? n : m-d; //minimum
            diagQuickSort(mat, d, 0, length);
        }
        else {
            length = (m > n-(d-m+1)) ? n-(d-m+1) : m; //minimum
            diagQuickSort(mat, 0, d-m+1, length);
        }
    }
    return mat;
}

/*-----------------------------------------Test---------------------------------------- */

//to allocate memory
int** matrix(int m, int n){
    int **mat = (int **) malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++){
        mat[i] = (int*) malloc(n * sizeof(int));
    }
    return mat;
}

void printMatrix(int** mat, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(){
    //generate arguments
    int** mat = matrix(2,3);
    mat[0][0] = 3; mat[0][1] = 10; mat[0][2] = 6; 
    mat[1][0] = 7; mat[1][1] = 2; mat[1][2] = 9;
    //printf("%d", mat[0][0]); 
    printMatrix(mat, 2, 3);

    printf("Sorted: \n");
    int matSize = 2;
    int matColSize[2] = {3,3};
    int rSize;
    int* returnSize = &rSize; int** returnColumnSizes;
    int** sortedMat = diagonalSort(mat, matSize, matColSize, returnSize, returnColumnSizes);
    printMatrix(mat, *returnSize, (*returnColumnSizes)[0]);
    return 0;
}