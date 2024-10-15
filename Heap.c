#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void heapfyBottomUp(int* H, int n);
void heapfyTopDown(int* H, int i);

int main() {
    int n, i;
    int* heap;

    printf("Numero de elementos da heap: ");
    scanf("%d", &n);

    heap = (int* ) calloc(n+1, sizeof(int));

    for(i = 0; i < n; i++) {
        scanf("%d", &heap[i+1]);
        heapfyTopDown(heap, i+1);
    }

    //heapfyBottomUp(heap, n+1);
    
    for(i = 0; i < n; i++)
        printf("%d ", heap[i+1]);
    printf("\n");

    free(heap);

    return 0;
}

void heapfyBottomUp(int* H, int n) {
    int i, k, v, j;
    bool heap;

    for(i = n/2; i >= 1; i--) {
        k = i;
        v = H[k];
        heap = false;

        while(!heap && 2*k <= n) {
            j = 2*k;

            if(j < n)
                if(H[j] < H[j+1])
                    j++;

            if(v > H[j])
                heap = true;
            else {
                H[k] = H[j];
                k = j;
            }
        }

        H[k] = v;
    }
}

void heapfyTopDown(int* H, int i) {
    bool heap = false;
    int pai;
    int tmp;

    while(!heap && i > 1) {
        pai = i/2;

        if(H[i] <= H[pai]) {
            heap = true;
        }
        else {
            tmp = H[pai];
            H[pai] = H[i];
            H[i] = tmp;
            i = pai;
        }
    }
}