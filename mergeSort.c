#include <stdio.h>
#include <stdlib.h>
//Algorithm implemented: MergeSort
//Author: ScierKnave (Dereck Piche)
//Language: C

//function copies the contents of p1 into p2
void copyLists(int* p1, int* p2, int length){
    for (int i = 0; i < length; i++){
        p2[i] = p1[i];
    }
}
//function prints out a lists
void printList(int* list, int length){
    for (int i = 0; i < length; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

//function sorts two ordered lists
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


int main(){
    //example test
    int list[15] = {3,7,2,4,5,6,7,4,5,6,5,7,4,2,3};
    mergeSort(list, 15);
    printList(list, 15);
    return 0;
}


