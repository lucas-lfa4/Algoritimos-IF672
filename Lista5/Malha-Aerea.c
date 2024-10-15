#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define UNVISITED 0
#define VISITED 1
#define INFINITO 1000000000

//Parte do grafo
typedef struct {
    int** matrix; //matriz de adjacencia
    int numEdge; //numero de arestas
    int numVertex; //numero de vertices
    int* Mark; //vetor de marcacao
    int* parent; //vetor de antecessores
} G;

G* create_graph(int n);
int n(G* g);
int weight(G* g, int v, int w);
void setEdge(G* g, int i, int j, int wt);
void setMark(G* g, int v, int mk);
int getMark(G* g, int v);
int first(G* g, int v);
int next(G* g, int v, int w);
void clear_graph(G* g);
void print_graph(G* g);
void prim(G* g, int* D);

//Parte da Heap
typedef struct {
    int predecessor;
    int vertice;
    int custo;
} Tripla;

typedef struct {
    Tripla* vetor;
    int tam;
    int last_pos;
} Heap;

Heap* create_heap(int n);
void heapfyTopDown(Heap* h, int index);
void heapfyBottomUp(Heap* h);
void insert(Heap* h, Tripla it);
Tripla removeMin(Heap* h);
void clear_heap(Heap* h);
void print_heap(Heap* h);

int main() {
    int i;
    int M, N;
    int idA, idB, c;
    int sum = 0;

    scanf("%d %d", &M, &N);
    G* g = create_graph(M);
    G* mst = create_graph(M);
    int D[M];

    for(i = 0; i < N; i++) {
        scanf("%d %d %d", &idA, &idB, &c);
        setEdge(g, idA, idB, c);
    }

    print_graph(g);

    prim(g, D);
    printf("\n");
    for(i = 0; i < M; i++) {
        setEdge(mst, i, g->parent[i], D[i]);
        if(D[i] != INFINITO)
            sum += D[i];
    }
    print_graph(mst);

    printf("%d\n", sum);
    
    clear_graph(g);
    clear_graph(mst);

    return 0;
}

G* create_graph(int n) {
    G* g = malloc(sizeof(G));
    if(g == NULL) {
        printf("Erro na alocacao de memoria do grafo\n");
        exit(1);
    }

    g->matrix = (int** ) calloc(n, sizeof(int*));
    if(g->matrix == NULL) {
        printf("Erro na alocacao de memoria da matriz de adjacencia\n");
        exit(1);
    }
    for(int i = 0; i < n; i++) {
        g->matrix[i] = (int* ) calloc(n, sizeof(int));
        if(g->matrix[i] == NULL) {
            printf("Erro na alocacao de memoria da matriz de adjacencia\n");
            exit(1);
        }

        for(int j = 0; j < n; j++)
            g->matrix[i][j] = -1;
    }

    g->Mark = (int* ) calloc(n, sizeof(int));
    if(g->Mark == NULL) {
        printf("Erro na alocacao de memoria do vetor de marcacao\n");
        exit(1);
    }

    g->parent = (int* ) calloc(n, sizeof(int));
    if(g->parent == NULL) {
        printf("Erro na alocacao de memoria do vetor de antecessores\n");
        exit(1);
    }

    g->numEdge = 0;
    g->numVertex = n;

    return g;
}

int n(G* g) {
    return g->numVertex;
}

int weight(G* g, int v, int w) {
    return g->matrix[v][w];
}

void setEdge(G* g, int i, int j, int wt) {
    if(g->matrix[i][j] == -1)
        g->numEdge++;

    g->matrix[i][j] = wt;
    g->matrix[j][i] = wt;
}

void setMark(G* g, int v, int mk) {
    g->Mark[v] = mk;
}

int getMark(G* g, int v) {
    return g->Mark[v];
}

int first(G* g, int v) {
    int i;

    for(i = 0; i < n(g); i++) {
        if(g->matrix[i][v] != -1)
            return i;
    }

    return n(g);
}

int next(G* g, int v, int w) {
    int i;

    for(i = w+1; i < n(g); i++) {
        if(g->matrix[i][v] != -1)
            return i;
    }

    return n(g);
}

void clear_graph(G* g) {
    int i;
    for(i = 0; i < n(g); i++)
        free(g->matrix[i]);
    
    free(g->matrix);
    free(g->Mark);
    free(g->parent);
    free(g);
}

void print_graph(G* g) {
    for(int i = 0; i < n(g); i++) {
        for(int j = 0; j < n(g); j++)
            printf("%d ", g->matrix[i][j]);
        
        printf("\n");
    }
}

void prim(G* g, int* D) {
    int i, v, p, w;
    Tripla tripla;
    tripla.custo = 0;
    tripla.vertice = 0;
    tripla.predecessor = 0;
    Heap* h = create_heap(n(g));

    for(i = 0; i < n(g); i++) {
        D[i] = INFINITO;
        g->parent[i] = -1;
        setMark(g, i, UNVISITED);
    }

    insert(h, tripla);
    D[0] = 0;

    for(i = 0; i < n(g); i++) {
        do {
            tripla = removeMin(h);
            print_heap(h);
            v = tripla.vertice;
            p = tripla.predecessor;

            if(v == -1) {
                clear_heap(h);
                return;
            }
        } while(getMark(g, v) == VISITED);
        printf("%d ainda nao foi visitado\n", v);
        setMark(g, v, VISITED);
        g->parent[v] = p;
        w = first(g, v);
        printf("Primeiro w eh %d\n", w);

        while(w < n(g)) {
            printf("D[%d] = %d e Mark[%d] = %d\n", w, D[w], w, getMark(g, w));
            if(getMark(g, w) != VISITED && D[w] > weight(g, v, w)) {
                printf("%d ainda nao foi visitado e D[%d] > distancia entre %d e %d\n", w, w, v, w);
                D[w] = weight(g, v, w);
                tripla.custo = D[w];
                tripla.predecessor = v;
                tripla.vertice = w;
                insert(h, tripla);
                print_heap(h);
            }

            w = next(g, v, w);
            printf("Proximo w eh %d\n", w);
        }
    }

    clear_heap(h);
}

Heap* create_heap(int n) {
    Heap* h = (Heap* ) malloc(sizeof(Heap));
    if(h == NULL) {
        printf("Erro na alocacao de memoria da heap\n");
        exit(1);
    }

    h->vetor = (Tripla* ) calloc(n*(n-1)/2 + 1, sizeof(Tripla));
    if(h->vetor == NULL) {
        printf("Erro na alocacao de memoria do vetor da heap\n");
        exit(1);
    }

    h->tam = n;
    h->last_pos = 0;

    return h;
}

void heapfyTopDown(Heap* h, int index) {
    int pai;
    Tripla tmp;
    bool heap = false;

    while(!heap && index > 1) {
        pai = index/2;

        if(h->vetor[pai].custo <= h->vetor[index].custo) {
            heap = true;
        }
        else {
            tmp = h->vetor[pai];
            h->vetor[pai] = h->vetor[index];
            h->vetor[index] = tmp;
            
            index = pai;
        }
    }
}

void heapfyBottomUp(Heap* h) {
    Tripla v;
    int i, j, k;
    bool heap = false;

    for(i = h->last_pos/2; i >= 1; i--) {
        k = i;
        v = h->vetor[k];
        heap = false;

        while(!heap && 2*k <= h->last_pos) {
            j = 2*k;

            if(j < h->last_pos)
                if(h->vetor[j].custo > h->vetor[j+1].custo)
                    j++;
            
            if(v.custo <= h->vetor[j].custo)
                heap = true;
            else {
                h->vetor[k] = h->vetor[j];
                k = j;
            }
        }

        h->vetor[k] = v;
    }
}

void insert(Heap* h, Tripla it) {
    if(h->last_pos < h->tam * (h->tam - 1)/2) {
        h->vetor[h->last_pos+1] = it;
        h->last_pos++;
        heapfyTopDown(h, h->last_pos);
    }
    else printf("Heap cheia!\n");
}

Tripla removeMin(Heap* h) {
    Tripla aRemover;
    aRemover.vertice = -1;

    if(h->last_pos < 1)
        return aRemover;
    else
        aRemover = h->vetor[1];

    h->vetor[1] = h->vetor[h->last_pos];
    h->last_pos--;
    heapfyBottomUp(h);

    return aRemover;
}

void clear_heap(Heap* h) {
    free(h->vetor);
    free(h);
}

void print_heap(Heap* h) {
    int i;

    printf("Heap agora esta assim: ");
    for(i = 1; i <= h->last_pos; i++) {
        printf("(%d, %d, %d) ", h->vetor[i].predecessor, h->vetor[i].vertice, h->vetor[i].custo);
    }
    printf("\n");
}