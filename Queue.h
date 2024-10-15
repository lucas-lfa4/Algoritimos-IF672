#include <stdio.h>
#include <stdlib.h>
#define ERRO -1

typedef struct Link {
    int element;
    struct Link* next;
} Link;

typedef struct {
    Link* front;
    Link* rear;
    int size;
} Queue;

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
        printf("A lista esta vazia\n");
        return ERRO;
    }
    else
        return q->front->next->element;
}

int lenght(Queue* q) {
    return q->size;
}

void clear_queue(Queue* q) {
    int i, qnt = q->size;

    for(i = 0; i < qnt; i++)
        dequeue(q);
}