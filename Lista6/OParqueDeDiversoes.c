#include <stdio.h>
#include <stdlib.h>

int W(int S, int B, int t);
void knapsack(int n, int maximo, int* C, int* S, int* B, int* Dp);

int main() {
    int N, V, i, maximo = 0;
    int* Dp = (int* ) calloc(25001, sizeof(int));
    for(i = 0; i < 25001; i++)
        Dp[i] = 0;

    scanf("%d", &N);
    int S[N], B[N], C[N];
    for(i = 0; i < N; i++) {
        scanf("%d %d %d", &S[i], &B[i], &C[i]);
        if(C[i] > maximo)
            maximo = C[i];
    }

    scanf("%d", &V);
    int K[V];
    for(i = 0; i < V; i++) {
        scanf("%d", &K[i]);
        if(K[i] > maximo)
            maximo = K[i];
    }

    knapsack(N, maximo, C, S, B, Dp);

    for(i = 0; i < V; i++)
        printf("%d: %d\n", i, Dp[K[i]]);

    free(Dp);

    return 0;
}

int W(int S, int B, int t) {
    if(S - (t-1)*(t-1)*B <= 0)
        return 0;
    else
        return S - (t-1)*(t-1)*B;
}

void knapsack(int n, int maximo, int* C, int* S, int* B, int* Dp) {
    int i, j, k;
    int Fmax, teto, acumulado, curr;

    for(i = 0; i < n; i++) {
        for(j = maximo; j >= C[i]; j--) {
            Fmax = 0;
            teto = j / C[i];
            acumulado = S[i];

            for(k = 1; k <= teto; k++) {
                curr = Dp[j-k*C[i]] + acumulado;

                if(curr > Fmax)
                    Fmax = curr;
                
                acumulado += W(S[i], B[i], k+1);
            }

            if(Fmax > Dp[j])
                Dp[j] = Fmax;
        }
    }
}