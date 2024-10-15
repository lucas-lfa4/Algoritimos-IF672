#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    unsigned int timeStamp;
    long int cliente;
} Conexao;

typedef struct {
    Conexao* array;
    int qnt;
    int max;
} Tabela;

int h(unsigned int T, int M);
int BS(Conexao* A, int l, int r, unsigned int K);
void inserir_na_tabela(Tabela* t, Conexao it, int pos);
void inserir_na_pos_certa(Tabela* t, Conexao it, int pos);

int main() {
    char linha[10];
    bool acabou = false;
    int n = 0, i, j, M, pos;
    unsigned int T;
    float L, LMAX;
    Tabela* aux;
    Conexao tmp;

    scanf("%d %f", &M, &LMAX);

    Tabela* tabela = (Tabela* ) calloc(M, sizeof(Tabela));
    for(i = 0; i < M; i++) {
        tabela[i].qnt = 0;
        tabela[i].max = 1;
        tabela[i].array = (Conexao* ) malloc(sizeof(Conexao));
    }

    while(!acabou) {
        scanf("%s", linha);

        if(strcmp(linha, "NEW") == 0) {
            scanf("%u %ld", &tmp.timeStamp, &tmp.cliente);

            L = (float) n/M;

            //rehashing
            if(L > LMAX) {
                //cria tabela auxiliar para o rehashing
                aux = (Tabela* ) calloc(M, sizeof(Tabela));
                aux = tabela;

                //nova tabela de tamanho 2*M + 1
                tabela = (Tabela* ) calloc(2*M + 1, sizeof(Tabela));
                for(i = 0; i <= 2*M; i++) {
                    tabela[i].qnt = 0;
                    tabela[i].max = 1;
                    tabela[i].array = (Conexao* ) malloc(sizeof(Conexao));
                }

                //inserir os elementos antigos na tabela nova
                for(i = 0; i < M; i++) {
                    for(j = 0; j < aux[i].qnt; j++)
                        inserir_na_pos_certa(tabela, aux[i].array[j], h(aux[i].array[j].timeStamp, 2*M + 1));

                    free(aux[i].array);
                }

                free(aux);

                M = 2*M + 1;
                //printf("M agora eh: %d\n", M);
            }

            pos = h(tmp.timeStamp, M);

            inserir_na_tabela(tabela, tmp, pos);

            printf("%d %d\n", pos, tabela[pos].qnt);
            n++;
        }
        else if(strcmp(linha, "QRY") == 0) {
            scanf("%u", &T);

            pos = h(T, M);

            j = BS(tabela[pos].array, 0, tabela[pos].qnt - 1, T);

            if(j == -1)
                printf("-1 -1\n");
            else {
                printf("%ld %d\n", tabela[pos].array[j].cliente, j);
                /*printf("Pilha %d:\n", pos);
                for(i = 0; i < tabela[pos].qnt; i++) {
                    printf("%u %ld\n", tabela[pos].array[i].timeStamp, tabela[pos].array[i].cliente);
                }*/
            }
        }
        else if(strcmp(linha, "END") == 0)
            acabou = true;
    }

    free(tabela);

    return 0;
}

int h(unsigned int T, int M) {
    return T % M;
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

void inserir_na_tabela(Tabela* t, Conexao it, int pos) {
    //se o array de pares estiver cheio, realocar mais espaco
    if(t[pos].qnt >= t[pos].max) {
        t[pos].max = 2*t[pos].max + 1;
        t[pos].array = (Conexao* ) realloc(t[pos].array, t[pos].max * sizeof(Conexao));
        if(t[pos].array == NULL) {
            printf("Erro na realocacao de memoria\n");
            exit(1);
        }
    }

    t[pos].array[t[pos].qnt] = it;
    t[pos].qnt++;
}

void inserir_na_pos_certa(Tabela* t, Conexao it, int pos) {
    int i = t[pos].qnt - 1;

    //se o array de pares estiver cheio, realocar mais espaco
    if(t[pos].qnt >= t[pos].max) {
        t[pos].max = 2*t[pos].max + 1;
        t[pos].array = (Conexao* ) realloc(t[pos].array, t[pos].max * sizeof(Conexao));
        if(t[pos].array == NULL) {
            printf("Erro na realocacao de memoria\n");
            exit(1);
        }
    }

    
    while(i >=0 && it.timeStamp < t[pos].array[i].timeStamp) {
        t[pos].array[i+1] = t[pos].array[i];
        i--;
    }

    //inserir no lugar correto
    t[pos].array[i+1] = it;
    t[pos].qnt++;
}