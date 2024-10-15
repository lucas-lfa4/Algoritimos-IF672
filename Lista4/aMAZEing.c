#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ERRO -1
#define UNVISITED 0
#define VISITED 1

//Parte de fila
typedef struct Link {
    int element;
    struct Link* next;
} Link;

typedef struct {
    Link* front;
    Link* rear;
    int size;
} Queue;

Link* create_link(int it, Link* nextval);
Link* create_link_initial(Link* nextval);
Queue* create_queue(void);
void enqueue(Queue* q, int it);
int dequeue(Queue* q);
int frontValue(Queue* q);
void print_queue(Queue* q);
void clear_queue(Queue* q);

//Parte do grafo
typedef struct {
    Queue** array;
    int numEdges;
    int numVertex;
    int* mark;
    int* componentes_conexos;
} G;

G* create_graph(int n);
int first(G* g, int v);
int next(G* g, int v, int w);
void setEdge(G* g, int v, int w);
void setMark(G* g, int v, int mk);
int getMark(G* g, int v);
void setCC(G* g, int v, int id);
int getCC(G* g, int v);
void clear_graph(G* g);
int isConnected(G* g, int start, int finish);

bool isWall(int P, int N);

void DFS(G* g, int v, int id);
void graphTraverse(G* g);

int main() {
    int K;
    int i, j;
    int N, M, Q;
    int *W, *A, *B;
    int resto, altura, deslocamento;
    G* g;

    scanf("%d", &K);

    for(i = 0; i < K; i++) {
        scanf("%d %d %d", &N, &M, &Q);

        g = create_graph(N*N);
        
        W = (int* ) calloc(M, sizeof(int));
        A = (int* ) calloc(Q, sizeof(int));
        B = (int* ) calloc(Q, sizeof(int));
        
        //faz as ligacoes do grafo
        for(j = 0; j < M; j++) {
            scanf("%d", &W[j]);

            if(isWall(W[j], N)) {
                resto = W[j] % (2*N-1);
                altura = (W[j] - resto) / (2*N-1);

                //printf("Tirando a parede %d e ligando os blocos %d e %d\n", W[j], N*altura+resto, N*altura+resto+1);

                setEdge(g, N*altura+resto, N*altura+resto+1);
            }
            else {
                resto = W[j] % (2*N-1);
                altura = (W[j] - resto) / (2*N-1);
                deslocamento = resto + 1 - N;

                //printf("Tirando o chao %d e ligando os blocos %d e %d\n", W[j], N*altura + deslocamento, N*(altura+1) + deslocamento);

                setEdge(g, N*altura + deslocamento, N*(altura+1) + deslocamento);
            }
        }

        graphTraverse(g);
        
        for(j = 0; j < Q; j++) {
            scanf("%d %d", &A[j], &B[j]);
            printf("%d.%d %d\n", i, j, isConnected(g, A[j], B[j]));
        }
        printf("\n");

        clear_graph(g);

        free(W);
        free(A);
        free(B);
    }





    return 0;
}

Link* create_link(int it, Link* nextval) {
    Link* n = (Link* ) malloc(sizeof(Link));

    n->element = it;
    n->next = nextval;

    return n;
}

Link* create_link_initial(Link* nextval) {
    Link* n = (Link* ) malloc(sizeof(Link));

    n->next = nextval;

    return n;
}

Queue* create_queue(void) {
    Queue* q = (Queue* ) malloc(sizeof(Queue));

    q->front = create_link_initial(NULL);
    q->rear = q->front;
    q->size = 0;

    return q;
}

void enqueue(Queue* q, int it) {
    q->rear->next = create_link(it, NULL);
    q->rear = q->rear->next;
    q->size++;
}

int dequeue(Queue* q) {
    Link* removido;
    int it;

    if(q->size == 0) {
        printf("Nao tem o que remover\n");
        return ERRO;
    }

    removido = q->front->next;
    it = q->front->next->element;
    q->front->next = q->front->next->next;

    if(q->front->next == NULL)
        q->rear = q->front;
    
    q->size--;
    free(removido);

    return it;
}

int frontValue(Queue* q) {
    if(q->size == 0) {
        return ERRO;
    }
    else
        return q->front->next->element;
}

void print_queue(Queue* q) {
    Link* curr = q->front;
    int i = 0;

    while(curr->next != NULL) {
        printf("elemento: %d ", curr->next->element);
        curr = curr->next;
        i++;
    }
    printf("\n");
}

void clear_queue(Queue* q) {
    int i, qnt = q->size;

    for(i = 0; i < qnt; i++)
        dequeue(q);

    free(q);
}

G* create_graph(int n) {
    G* g = (G* ) malloc(sizeof(G));

    g->array = (Queue** ) calloc(n, sizeof(Queue*));
    g->mark = (int* ) calloc(n, sizeof(int));
    g->componentes_conexos = (int* ) calloc(n, sizeof(int));
    for(int i = 0; i < n; i++) {
        g->array[i] = create_queue();
        g->mark[i] = UNVISITED;
        g->componentes_conexos[i] = -1;
    }

    g->numEdges = 0;
    g->numVertex = n;

    return g;
}

int first(G* g, int v) {
    return frontValue(g->array[v]);
}

int next(G* g, int v, int w) {
    Link* curr = g->array[v]->front;

    while(curr->next != NULL) {
        if(curr->next->element == w) {
            if(curr->next->next != NULL)
                return curr->next->next->element;
            else
                return ERRO;
        }

        curr = curr->next;
    }

    return ERRO;
}

void setEdge(G* g, int v, int w) {
    enqueue(g->array[v], w);
    enqueue(g->array[w], v);
}

void setMark(G* g, int v, int mk) {
    g->mark[v] = mk;
}

int getMark(G* g, int v) {
    return g->mark[v];
}

void setCC(G* g, int v, int id) {
    g->componentes_conexos[v] = id;
}

int getCC(G* g, int v) {
    return g->componentes_conexos[v];
}

void clear_graph(G* g) {
    int i;

    for(i = 0; i < g->numVertex; i++)
        clear_queue(g->array[i]);

    free(g->array);
    free(g->mark);
    free(g->componentes_conexos);
    free(g);
}

int isConnected(G* g, int start, int finish) {
    if(getCC(g, start) == getCC(g, finish))
        return 1;
    else return 0;
}

bool isWall(int P, int N) {
    if(P % (2*N-1) <= N-2)
        return true;
    else
        return false;
}

//percorrer o grafo ate onde der e colocar id em componentes_conexos[]
void DFS(G* g, int v, int id) {
    int w;

    setMark(g, v, VISITED);
    setCC(g, v, id);
    w = first(g, v);

    while(w != -1) {
        if(getMark(g, w) == UNVISITED) {
            DFS(g, w, id);
        }

        w = next(g, v, w);
    }
}

void graphTraverse(G* g) {
    int i, id = 0;

    for(i = 0; i < g->numVertex; i++) {
        if(getCC(g, i) == -1) {
            DFS(g, i, id);
            id++;
        }
    }
}