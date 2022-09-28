#include <stdio.h>
#include <stdlib.h>
/*
Description: Taking a matrix as input, return a copy were all the elements are sorted 
on it's diagonal. (Problem #1329 of LeetCode)
Author: ScierKnave 
Language: C
*/



/*-----------------------------------------Utilities---------------------------------------- */
//function copies the contents of p1 into p2
void copyLists(int* p1, int* p2, int length){
    for (int i = 0; i < length; i++){
        p2[i] = p1[i];
    }
}

//return minimum of two integers
int minimum(int a, int b){
    if (a < b) { return a; }
    return b;
}

//allocate memory for a m * n matrix and return it's pointer
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

/*-----------------------------------------MergeSort---------------------------------------- */

//function merges two ordered lists
void merge(int* list1, int len1, int* list2, int len2){
    int i, j, k, temp; i = j = k = temp = 0;
    //create temporary copies of list1 and list2
    int *tempL1; int *tempL2;
    tempL1 = (int*) malloc(sizeof(int)*len1); 
    tempL2 = (int*) malloc(sizeof(int)*len2);
    copyLists(list1, tempL1, len1); 
    copyLists(list2, tempL2, len2);
    while(i < len1 & j < len2){
        if (tempL1[i] <= tempL2[j]) {
            list1[k] = tempL1[i]; i++;
        }
        else { list1[k] = tempL2[j]; j++; }
        k++;
    }
    while(i < len1) { list1[k] = tempL1[i]; i++; k++; }
    while(j < len2) { list1[k] = tempL2[j]; j++; k++; }
    free(tempL1); free(tempL2); //free temp. list copies
}

void mergeSort(int *list, int length){
    if (length >= 2) {
        int halfLen, rest, len1, len2; //declare variables
        halfLen = length / 2; rest = length % 2;
        len1 = halfLen + rest; len2 = length - len1;
        int* list2 = list + len1;
        //sort left and right lists recursively
        mergeSort(list, len1); mergeSort(list2, len2);
        //merge left and right lists
        merge(list, len1, list2, len2); 
    }
}




/*-----------------------------------------Diagonal Sort---------------------------------------- */

//turns diagonal of a matrix into a malloced list and returns pointer of said list
int* diagToList(int** mat, int i, int j, int m, int n){
    //find length of list
    int length = minimum(m-i, n-j); 
    //create list
    int* list = (int*)malloc(sizeof(int)*length); //allocate memory for list
    int k = 0;
    while (i < m & j < n) {
        list[k] = mat[i][j];
        k++; i++, j++;
    }
    return list;
}

//takes list and copies it into diagonal of matrix 
void setDiag(int** mat, int i, int j, int m, int n, int* list){
    int k = 0;
    while (i < m & j < n) {
        mat[i][j] = list[k];
        i++, j++; k++;
    }
}

//sorts the diagonal starting i and j
void dSort(int** mat, int i, int j, int m, int n)
{
    int* list = diagToList(mat, i, j, m, n);
    int length = minimum(m-i, n-j); 
    mergeSort(list, length);
    setDiag(mat, i, j, m, n, list);
    free(list);
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
            dSort(mat, d, 0, m, n);
        }
        //if diag starts in first line AND not in first column
        else {
            dSort(mat, 0, d-m+1, m, n);
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