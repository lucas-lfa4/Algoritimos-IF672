#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <linked_list.h>

#define UNVISITED 0
#define VISITED 1


//Grafo nao-direcionado sem pesos
typedef struct {
    List** array;
    int numEdges;
    int numVertex;
    int* mark;
} G;

G* create_graph(int n) {
    G* g = (G* ) malloc(sizeof(G));

    g->array = (List** ) calloc(n, sizeof(List*));
    if(g->array == NULL) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    g->mark = (int* ) calloc(n, sizeof(int));
    if(g->mark == NULL) {
       printf("Erro na alocacao de memoria\n");
        exit(1); 
    }

    for(int i = 0; i < n; i++) {
        g->array[i] = create_list();
        g->mark[i] = UNVISITED;
    }

    g->numEdges = 0;
    g->numVertex = n;

    return g;
}

int n(G* g) {
    return g->numVertex;
}

int e(G* g) {
    return g->numEdges;
}

int first(G* g, int v) {
    if(g->array[v]->cnt == 0)
        return -1;
    else
        return g->array[v]->head->next->element;
}

int next(G* g, int v, int w) {
    moveToStart(g->array[v]);

    while(g->array[v]->curr->next != NULL) {
        if(g->array[v]->curr->next->element == w) {
            if(g->array[v]->curr->next->next != NULL)
                return g->array[v]->curr->next->next->element;
            else
                return -1;
        }

        next(g->array[v]);
    }

    return -1;
}

bool isEdge(G* g, int i, int j) {
    moveToStart(g->array[i]);

    while(g->array[i]->curr->next != NULL) {
        if(g->array[i]->curr->next->element == j)
            return true;
        else
            next(g->array[i]);
    }

    return false;
}

void setEdge(G* g, int i, int j) {
    if(isEdge(g, i, j)) 
        return;
    else {
        moveToStart(g->array[i]);
        insert(g->array[i], j);

        moveToStart(g->array[j]);
        insert(g->array[j], i);

        g->numEdges++;
    }
}

void setMark(G* g, int v, int mk) {
    g->mark[v] = mk;
}

int getMark(G* g, int v) {
    return g->mark[v];
}