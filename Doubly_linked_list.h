#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Link {
    int element;
    struct Link* prev;
    struct Link* next;
} Link;

typedef struct {
    Link* head;
    Link* tail;
    Link* curr;
    int cnt;
} List;

Link* create_link(int it, Link* prevVal, Link* nextVal) {
    Link* n = (Link* ) malloc(sizeof(Link));

    n->element = it;
    n->prev = prevVal;
    n->next = nextVal;

    return n;
}

Link* create_link_initial(Link* prevVal, Link* nextVal) {
    Link* n = (Link* ) malloc(sizeof(Link));

    n->prev = prevVal;
    n->next = nextVal;

    return n;
}

List* create_list(void) {
    List* l = (List* ) malloc(sizeof(List));
    
    l->head = create_link_initial(NULL, NULL);
    l->tail = create_link_initial(l->head, NULL);
    l->head->next = l->tail;
    l->curr = l->head;
    l->cnt = 0;

    return l;
}

void insert(List* l, int it) {
    l->curr->next = create_link(it, l->curr, l->curr->next);
    l->curr->next->next->prev = l->curr->next;
    l->cnt++;
}

void append(List* l, int it) {
    l->head->next = create_link(it, l->head, l->head->next);
    l->head->next->next->prev = l->head->next;
    l->cnt++;
}

int remove_from_list(List* l) {
    if(l->curr->next == l->tail) {
        printf("Nao tem o que remover\n");
        return 0;
    }

    Link* remover = l->curr->next;
    int it = remover->element;

    l->curr->next = l->curr->next->next;
    l->curr->next->prev = l->curr;
    l->cnt--;

    free(remover);

    return it;
}

void moveToStart(List* l) {
    l->curr = l->head;
}

void moveToEnd(List* l) {
    l->curr = l->tail->prev;
}

void prev(List* l) {
    if(l->curr->prev != NULL)
        l->curr = l->curr->prev;
}

void next(List* l) {
    if (l->curr->next != l->tail)
        l->curr = l->curr->next;
}

void clear(List* l) {
    int i = 0, j = l->cnt;
    moveToStart(l);

    for(i = 0; i < j; i++)
        remove_from_list(l);
}

int lenght(List* l) {
    return l->cnt;
}

int currPos(List* l) {
    int i = 0;
    Link* aux = l->head;

    while(aux != l->curr) {
        aux = aux->next;
        i++;
    }

    return i;
}

void moveToPos(List* l, int pos) {
    int i = 0;
    moveToStart(l);

    for(i = 0; i < pos; i++)
        next(l);
}

int getValue(List* l) {
    return l->curr->element;
}