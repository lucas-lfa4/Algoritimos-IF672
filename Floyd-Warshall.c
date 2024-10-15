#include "Graph_matrix.h"
#include <string.h>
#define INFINITO 1000000

void Floyd(G* g, int** D);

int main() {
    int** D;
    int n, i, j, wt;
    char linha[20];
    bool acabou = false;

    scanf("%d", &n);
    G* g = create_graph(n);
    D = (int** ) calloc(n, sizeof(int*));
    for(i = 0; i < n; i++)
        D[i] = (int* ) calloc(n, sizeof(int));

    
    while(!acabou) {
        scanf("%s", linha);

        if(strcmp("NEW", linha) == 0) {
            scanf(" %d %d %d", &i, &j, &wt);

            setEdge(g, i, j, wt);
        }
        else if(strcmp("RM", linha) == 0) {
            scanf("%d %d", &i, &j);

            delEdge(g, i, j);
        }
        else if(strcmp("END", linha) == 0) {
            acabou = true;
        }
    }

    print_graph(g);
    Floyd(g, D);

    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++)
            printf("%d ", D[i][j]);

        printf("\n");
    }



    clear(g);
    
    return 0;
}

void Floyd(G* g, int** D) {
    int i, j, k;

    for(i = 0; i < n(g); i++) {
        for(j = 0; j < n(g); j++) {
            if(i == j)
                D[i][j] = 0;
            else if(weight(g, i, j) != 0)
                D[i][j] = weight(g, i, j);
            else
                D[i][j] = INFINITO;
        }
    }

    for(k = 0; k < n(g); k++)
        for(i = 0; i < n(g); i++)
            for(j = 0; j < n(g); j++)
                if(D[i][k] != INFINITO && D[k][j] != INFINITO && D[i][j] > D[i][k] + D[k][j])
                    D[i][j] = D[i][k] + D[k][j];
}