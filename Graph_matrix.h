#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"
#define UNVISITED 0
#define VISITED 1

typedef struct {
    int** matrix; // matriz de adjacencia
    int numEdge; // numero de arestas
    int numVertex; // numero de vertices
    int* Mark; // vetor de marcacao auxiliar
    int* parent; // vetor dos antecessores
} G;

G* create_graph(int n) {
    G* g = (G* ) malloc(sizeof(G));

    g->Mark = (int* ) calloc(n , sizeof(int));
    g->parent = (int* ) calloc(n , sizeof(int));
    g->matrix = (int** ) calloc(n, sizeof(int* ));
    for(int i = 0; i < n; i++) {
        g->matrix[i] = (int* ) calloc(n, sizeof(int));
        for(int j = 0; j < n; j++)
            g->matrix[i][j] = 0;
        
        g->Mark[i] = UNVISITED;
        g->parent[i] = -1;
    }
    g->numEdge = 0;
    g->numVertex = n;

    return g;
}

int n(G* g) {
    return g->numVertex;
}

int e(G* g) {
    return g->numEdge;
}

int first(G* g, int v) {
    for(int i = 0; i < n(g); i++)
        if(g->matrix[v][i] != 0)
            return i;

    return n(g);
}

int next(G* g, int v, int w) {
    for(int i = w+1; i < n(g); i++)
        if(g->matrix[v][i] != 0)
            return i;

    return n(g);
}

int weight(G* g, int v, int w) {
    return g->matrix[v][w];
}

void setEdge(G* g, int i, int j, int wt) {
    if(wt == 0) {
        printf("0 nao ne animal\n");
        return;
    }

    if(g->matrix[i][j] == 0)
        g->numEdge++;

    g->matrix[i][j] = wt;
}

void delEdge(G* g, int i, int j) {
    if(g->matrix[i][j] == 0)
        g->numEdge--;

    g->matrix[i][j] = 0;
}

void setMark(G* g, int v, int mk) {
    g->Mark[v] = mk;
}

int getMark(G* g, int v) {
    return g->Mark[v];
}

void preVisit(G* g, int v) {
    // faca alguma coisa
}

void posVisit(G* g, int v) {
    // faca outra coisa
}

//Encaminhamento em profundidade
void DFS(G* g, int v) {
    int w;

    preVisit(g, v);
    setMark(g, v, VISITED);
    w = first(g, v);

    while(w < n(g)) {
        if(getMark(g, w) == UNVISITED)
            DFS(g, w);
        
        w = next(g, v, w);
    }

    posVisit(g, v);
}

//Encaminhamento em largura
void BFS(G* g, int start) {
    int v, w;

    Queue* q = create_queue();
    enqueue(q, start);
    setMark(g, start, VISITED);

    while(lenght(q) > 0) {
        v = dequeue(q);
        preVisit(g, v);
        w = first(g, v);

        while(w < n(g)) {
            if(getMark(g, w) == UNVISITED) {
                setMark(g, w, VISITED);

                enqueue(q, w);
            }

            w = next(g, v, w);
        }
        
        posVisit(g, v);
    }

    clear_queue(q);
}

//Percorre todo o grafo
void graphTraverse(G* g) {
    int v = 0;

    for(v = 0; v < n(g) - 1; v++)
        setMark(g, v, UNVISITED);

    for(v = 0; v < n(g) - 1; v++)
        if(getMark(g, v) == UNVISITED)
            DFS(g, v);
}

void clear(G* g) {
    for(int i = 0; i < n(g); i++)
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