#include "Graph_matrix.h"
#include <string.h>
#define INFINITO 1000000

typedef struct {
    int predecessor;
    int vertice;
    int custoAcumulado;
} Tripla;

typedef struct {
    Tripla* vetor;
    int tam;
    int last_pos;
} Heap;

Heap* createHeap(int tam);
void insert(Heap* H, Tripla it);
Tripla removeMin(Heap* H);
void swap(Tripla* A, Tripla* B);
void heapfyTopDown(Heap* H);
void heapfyBottomUp(Heap* H);
void clear_heap(Heap* H);
void print_heap(Heap* H);

void Dijkstra(G* g, int s, int* D);

int main() {
    int n, i, j, wt;
    char linha[20];
    bool acabou = false;
    int* D;

    scanf("%d", &n);
    G* g = create_graph(n);
    D = (int* ) calloc(n, sizeof(int));

    while(!acabou) {
        scanf("%s", linha);

        if(strcmp("NEW", linha) == 0) {
            scanf(" %d %d %d", &i, &j, &wt);

            setEdge(g, i, j, wt);
            setEdge(g, j, i, wt);
        }
        else if(strcmp("RM", linha) == 0) {
            scanf("%d %d", &i, &j);

            delEdge(g, i, j);
            //delEdge(g, j, i);
        }
        else if(strcmp("END", linha) == 0)
            acabou = true;
    }

    printf("O grafo ficou:\n");
    print_graph(g);

    Dijkstra(g, 0, D);

    printf("D: ");
    for(i = 0; i < n; i++)
        printf("%d ", D[i]);
    printf("\n");


    clear(g);
    free(D);

    return 0;
}

Heap* createHeap(int tam) {
    Heap* H = malloc(sizeof(Heap));

    H->last_pos = 1;
    H->tam = tam;
    H->vetor = (Tripla* ) calloc(tam*(tam-1) + 1, sizeof(Tripla));

    return H;
}

void insert(Heap* H, Tripla it) {
    if(H->last_pos >= H->tam*(H->tam-1) + 1) {
        printf("Heap cheia\n");
        return;
    }

    H->vetor[H->last_pos] = it;
    heapfyTopDown(H);
    H->last_pos++;
}

Tripla removeMin(Heap* H) {
    Tripla aRemover;
    aRemover.vertice = -1;

    if(H->last_pos >= 1) {
        return aRemover;
    }
    else {
        aRemover = H->vetor[1];
        swap(&H->vetor[1], &H->vetor[H->last_pos-1]);
        H->last_pos--;
        heapfyBottomUp(H);
        return aRemover;
    }
}

void swap(Tripla* A, Tripla* B) {
    Tripla tmp = *A;

    *A = *B;
    *B = tmp;
}

void heapfyTopDown(Heap* H) {
    bool acabou = false;
    int pai;
    int i = H->last_pos;

    while(!acabou && i > 1) {
        pai = i/2;

        if(H->vetor[i].custoAcumulado >= H->vetor[pai].custoAcumulado) {
            acabou = true;
        }
        else {
            swap(&H->vetor[i], &H->vetor[pai]);
            i = pai;
        }
    }
}

void heapfyBottomUp(Heap* H) {
    int i, k, j;
    Tripla v;
    bool heap = false;

    for(i = (H->last_pos-1)/2; i >=1; i--) {
        k = i;
        v = H->vetor[k];
        heap = false;

        while(!heap && 2*k <= H->last_pos-1) {
            j = 2*k;

            if(j < H->last_pos-1)
                if(H->vetor[j].custoAcumulado > H->vetor[j+1].custoAcumulado)
                    j++;

            if(v.custoAcumulado < H->vetor[j].custoAcumulado) {
                heap = true;
            }
            else {
                H->vetor[k] = H->vetor[j];
                k = j;
            }
        }

        H->vetor[k] = v;
    }
}

void clear_heap(Heap* H) {
    free(H->vetor);
    free(H);
}

void print_heap(Heap* H) {
    int i;

    for(i = 1; i < H->last_pos; i++) {
        printf("%d %d %d\n", H->vetor[i].custoAcumulado, H->vetor[i].predecessor, H->vetor[i].vertice);
    }
}

void Dijkstra(G* g, int s, int* D) {
    int i, p, v, w;
    Tripla t;
    Heap* H = createHeap(n(g)*(n(g)-1)/2 + 1);

    for(i = 0; i < n(g); i++) {
        D[i] = INFINITO;
        g->parent[i] = -1;
        setMark(g, i, UNVISITED);
    }

    H->vetor[1].predecessor = s;
    H->vetor[1].vertice = s;
    H->vetor[1].custoAcumulado = 0;
    D[s] = 0;

    for(i = 0; i < n(g); i++) {
        do {
            t = removeMin(H);
            v = t.vertice;
            p = t.predecessor;

            if(v == -1) {
                clear_heap(H);
                return;
            }
        } while(getMark(g, v) == VISITED);

        setMark(g, v, VISITED);
        g->parent[v] = p;

        w = first(g, v);
        while(w < n(g)) {
            if(getMark(g, w) == UNVISITED && D[w] > D[v] + weight(g, v, w)) {
                D[w] = D[v] + weight(g, v, w);
                t.predecessor = v;
                t.vertice = w;
                t.custoAcumulado = D[w];
                insert(H, t);
            }

            w = next(g, v, w);
        }
    }

    clear_heap(H);
}