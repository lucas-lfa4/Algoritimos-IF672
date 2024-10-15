#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Link{
    int element;
    struct Link* next;
} Link;

typedef struct {
    Link* head;
    Link* tail;
    Link* curr;
    int cnt;
} List;

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

List* create_list(void) {
    List* l = (List* ) malloc(sizeof(List));

    l->curr = create_link_initial(NULL);
    l->tail = l->curr;
    l->head = l->curr;
    l->cnt = 0;

    return l;
}

void insert(List* l, int it) {
    l->curr->next = create_link(it, l->curr->next);

    if(l->tail == l->curr) {
        l->tail = l->curr->next;
    }

    l->cnt++;
}

void append(List* l, int it) {
    l->head->next = create_link(it, l->head->next);

    if(l->tail == l->head) {
        l->tail = l->head->next;
    }

    l->cnt++;
}

void moveToStart(List* l) {
    l->curr = l->head;
}

void moveToEnd(List* l) {
    l->curr = l->tail;
}

void prev(List* l) {
    if(l->curr == l->head) { return; }

    Link* tmp = l->head;

    while(tmp->next != l->curr) {
        tmp = tmp->next;
    }

    l->curr = tmp;
}

void next(List* l) {
    if(l->curr != l->tail) {
        l->curr = l->curr->next;
    }
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

int remove_from_list(List* l) {
    if(l->curr->next == NULL) {
        printf("Nao tem o que remover\n");
        return 0;
    }

    int it = l->curr->next->element;
    Link* removido = l->curr->next;

    if(l->tail == l->curr->next) {
        l->tail = l->curr;
    }

    l->curr->next = l->curr->next->next;
    l->cnt--;

    free(removido);

    return it;
}

void clear_list(List* l) {
    int i = 0, j = l->cnt;
    moveToStart(l);

    for(i = 0; i < j; i++)
        remove_from_list(l);
}

void print(List* l) {
    int i = 0;
    moveToStart(l);

    for(i = 0; i < l->cnt; i++) {
        printf("Posicao %d, elemento %i\n", i+1, l->curr->next->element);
        next(l);
    }

    printf("Posição do cursor: %d\n", currPos(l));
}