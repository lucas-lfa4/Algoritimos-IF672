#include <stdio.h>
#define TAM 24

void MergeSort(int* array, int l, int r, int tam);
void Merge(int* array, int l, int r, int tam);

int main() {
    int i;
    int array[TAM] = {28, 75, 18, 63, 49, 43, 13, 77, 51, 28, 0, 11, 35, 68, 97, 42, 53, 63, 36, 25, 89, 3, 5, 4};

    MergeSort(array, 0, 23, 24);

    for(i = 0; i < TAM; i++)
        printf("%d ", array[i]);

    return 0;
}

void MergeSort(int* array, int l, int r, int tam) {
    int m;
    if(l < r) {
        m = (l+r)/2;
        MergeSort(array, l, m, tam);
        MergeSort(array, m+1, r, tam);
        Merge(array, l, r, tam);
    }
}

void Merge(int* array, int l, int r, int tam) {
    int i, m, i1, i2, curr;
    int tmp[tam];
    for(i = l; i <= r; i++)
        tmp[i] = array[i];

    m = (l+r)/2;
    i1 = l;
    i2 = m+1;

    for(curr = l; curr <= r; curr++) {
        if(i1 == m + 1)
            array[curr] = tmp[i2++];
        else if(i2 > r) 
            array[curr] = tmp[i1++];
        else if (tmp[i1] <= tmp[i2])
            array[curr] = tmp[i1++];
        else array[curr] = tmp[i2++];
    }
}