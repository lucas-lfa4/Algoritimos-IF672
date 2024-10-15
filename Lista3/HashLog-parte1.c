#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    unsigned int timeStamp;
    unsigned int cliente;
} Conexao;

int BS(Conexao* A, int l, int r, unsigned int K);

int main() {
    char linha[10];
    bool acabou = false;
    int n = 0, max = 2*n, j;
    Conexao* array = (Conexao* ) malloc(sizeof(Conexao));
    if(array == NULL) {
        printf("Erro na realocacao de memoria\n");
        return 1;
    }
    Conexao tmp;


    while(!acabou) {
        scanf("%s", linha);

        if(strcmp(linha, "NEW") == 0) {
            scanf("%u %u", &tmp.timeStamp, &tmp.cliente);
            n++;
            if(n >= max) {
                max = 2*n;
                array = (Conexao* ) realloc(array, max * sizeof(Conexao));
                if(array == NULL) {
                    printf("Erro na realocacao de memoria\n");
                    return 1;
                }
            }

            array[n-1] = tmp;
        }
        else if(strcmp(linha, "QRY") == 0) {
            scanf("%u", &tmp.timeStamp);

            j = BS(array, 0, n-1, tmp.timeStamp);

            if(j == -1)
                printf("-1 -1\n");
            else
                printf("%u %d\n", array[j].cliente, j);
        }
        else if(strcmp(linha, "END") == 0)
            acabou = true;
    }

    free(array);

    return 0;
}

int BS(Conexao* A, int l, int r, unsigned int K) {
    int m;

    if (l <= r) {
        m = (l+r)/2;

        if(K == A[m].timeStamp)
            return m;
        else if(K < A[m].timeStamp)
            return BS(A, l, m-1, K);
        else
            return BS(A, m+1, r, K);
    }
    else
        return -1;
}