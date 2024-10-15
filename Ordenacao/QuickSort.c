#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_VETORES 10
#define TAM 100


void QuickSort(int* A, int l, int r);
void Swap(int* A, int* B);
int HoarePartition(int* A, int l, int r);

int main() {
    srand(time(NULL));
    int i, j;
    int vetor[NUM_VETORES][TAM];

    for(i = 0; i < NUM_VETORES; i++) {
        printf("vetor %d: ", i+1);

        for(j = 0; j < TAM; j++) {
            vetor[i][j] = rand() % 100;
            printf("%d ", vetor[i][j]);
        }
        printf("\nordenado: ");

        QuickSort(vetor[i], 0 , TAM-1);

        for(j = 0; j < TAM; j++)
            printf("%d ", vetor[i][j]);
        printf("\n");
    }
    

    return 0;
}

void QuickSort(int* A, int l, int r) {
    int s;
    if(l < r) {
        s = HoarePartition(A, l, r);
        QuickSort(A, l, s-1);
        QuickSort(A, s+1, r);
    }
}

void Swap(int* A, int* B) {
    int aux;
    aux = *A;
    *A = *B;
    *B = aux;
}

int HoarePartition(int* A, int l, int r) {
    int p, i, j;

    p = A[(rand() % (r-l+1)) + l];
    i = l;
    j = r+1;

    do {
        do {
            i++;
        } while(A[i] < p && i < r);

        do {
            j--;
        } while(A[j] > p);

        Swap(&A[i], &A[j]);
    } while(i < j);

    Swap(&A[i], &A[j]);
    Swap(&A[l], &A[j]);
    
    return j;
}