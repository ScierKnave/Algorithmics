#include <stdio.h>
#include <stdlib.h>
/*
Description: Taking a matrix as input, return a copy were all the elements are sorted 
on it's diagonal. (Problem #1329 of LeetCode)
Author: ScierKnave 
Language: C
*/

/*-----------------------------------------Utilities---------------------------------------- */



//return minimum of two integers
int minimum(int a, int b){
    if (a < b) { return a; }
    return b;
}

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

/*-----------------------------------------Diagonal Sort---------------------------------------- */



void Switch(int** mat, int i, int j, int i2, int j2){
    int temp = mat[i][j];
    mat[i][j] = mat[i2][j2];
    mat[i2][j2] = temp;
}


//sorts the diagonal starting i and j
void diagQuickSort(int** mat, int i, int j, int length)
{
    if (length < 2){
        return;
    }
    int pivot = mat[i][j];
    int a = 0; int b = length-1;

    while (a < b) {
        while(mat[i+a][j+a] <= pivot & a < b){
            a++;
        }
        while(mat[i+b][j+b] > pivot & a < b){
            b--;
        }
        Switch(mat, i+a, j+a, i+b, j+b);
    }
    Switch(mat, i, j, i+a, j+a);
    diagQuickSort(mat, i, j, a); 
    diagQuickSort(mat, i+a+1, j+a+1, length-b);
}




//create a copy of mat were all the elements on it's diagonal are sorted
int** diagonalSort(int** mat, int matSize, int* matColSize, int* returnSize, int** returnColumnSizes){

    //rename variables
    int m = matSize; //number of lines
    int n =  matColSize[0]; //number of columns
    //set sizes of returned matrix
    *returnSize = m;
    *returnColumnSizes = malloc(sizeof(int)*m);
    for (int i = 0; i < m; i++) (*returnColumnSizes)[i] = n;
    
    //sort all the diagonals
    for (int d = 0; d < m + n -1; d++){
        //if diag starts in first column
        if (d < m){
            int length = minimum(m-d, n);
            diagQuickSort(mat, d, 0, length);
        }
        //if diag starts in first line AND not in first column
        else {
            int length = minimum(m, n-(d-m+1));
            diagQuickSort(mat, 0, d-m+1, length);
        }
    }
    return mat;
}

/*-----------------------------------------Main---------------------------------------- */

int main(){
    //generate arguments
    int** mat = matrix(2,3);
    mat[0][0] = 3; mat[0][1] = 10; mat[0][2] = 6; 
    mat[1][0] = 7; mat[1][1] = 2; mat[1][2] = 9;
    //printf("%d", mat[0][0]); 
    printMatrix(mat, 2, 3);
    printf("\n");
    int matSize = 2;
    int matColSize[2] = {3,3};
    int rSize;
    int* returnSize = &rSize; int** returnColumnSizes;
    int** sortedMat = diagonalSort(mat, matSize, matColSize, returnSize, returnColumnSizes);
    printMatrix(mat, *returnSize, (*returnColumnSizes)[0]);
    return 0;
}