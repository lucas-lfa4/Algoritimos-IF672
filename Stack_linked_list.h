#include <stdio.h>
#include <stdlib.h>

typedef struct Link {
    int element;
    struct Link* next;
} Link;

typedef struct {
    Link* top;
    int size;
} Stack;

Link* create_link(int it, Link* nextval) {
    Link* n = (Link* ) malloc(sizeof(Link));

    n->element = it;
    n->next = nextval;

    return n;
}

Stack* create_stack(void) {
    Stack* s = (Stack* ) malloc(sizeof(Stack));

    s->top = NULL;
    s->size = 0;

    return s;
}

void push(Stack* s, int it) {
    s->top = create_link(it, s->top);
    s->size++;
}

int pop(Stack* s) {
    if(s->top == NULL) {
        printf("Nao tem o que retirar\n");
        return -1;
    }

    int it = s->top->element;
    Link* tmp = s->top;

    s->top = s->top->next;
    s->size--;

    free(tmp);

    return it;
}

int topValue(Stack* s) {
    if(s->top == NULL) {
        printf("A pilha nao tem elementos\n");
        return -1;
    }
    else return s->top->element;
}

int lenght(Stack* s) {
    return s->size;
}

void clear(Stack* s) {
    int i = 0, j = s->size;

    while(i < j) {
        pop(s);
        i++;
    }
}