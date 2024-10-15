#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Link {
    int element;
    struct Link* next;
} Link;

typedef struct {
    Link* head;
    Link* tail;
    Link* curr;
    int cnt;
} Stack;

Link* create_link(int it, Link* nextVal);
Link* create_link_initial(Link* nextVal);
Stack* create_stack(void);
void insert(Stack* s, int it);
void remove_from_stack(Stack* s);
bool TemMesmaParidade(int a, int b);
void moveToStart(Stack* s);
void calculo_pilha(Stack* s);
void clear(Stack* s);

int main() {
    int n, i, j;

    scanf("%d", &n);

    Stack* pilhas[n];

    for(i = 0; i < n; i++) {
        pilhas[i] = create_stack();

        do {
            scanf("%i", &j);
            if(j != 0) {
                insert(pilhas[i], j);
                calculo_pilha(pilhas[i]);
            }
        } while(j != 0);
    }

    for(i = 0; i < n; i++) {
        if(pilhas[i]->head->next != NULL)
            printf("Pilha %d: %d %i\n", i+1, pilhas[i]->cnt, pilhas[i]->head->next->element);
        else printf("Pilha %d: %d -1\n", i+1, pilhas[i]->cnt);
    }

    for(i = 0; i < n; i ++)
        clear(pilhas[i]);

    return 0;
}

Link* create_link(int it, Link* nextVal) {
    Link* n = (Link* ) malloc(sizeof(Link));

    n->element = it;
    n->next = nextVal;

    return n;
}

Link* create_link_initial(Link* nextVal) {
    Link* n = (Link* ) malloc(sizeof(Link));

    n->next = nextVal;

    return n;
}

Stack* create_stack(void) {
    Stack* s = (Stack* ) malloc(sizeof(Stack));

    s->cnt = 0;
    s->head = create_link_initial(NULL);
    s->curr = s->head;
    s->tail = s->head;

    return s;
}

void insert(Stack* s, int it) {
    s->curr->next = create_link(it, s->curr->next);
    
    if(s->curr == s->tail)
        s->tail = s->curr->next;

    s->cnt++;
}

void remove_from_stack(Stack* s) {
    if(s->curr->next == NULL)
        return;
    
    Link* tmp = s->curr->next;

    if(s->tail == s->curr->next)
        s->tail = s->curr;

    s->curr->next = s->curr->next->next;
    s->cnt--;

    free(tmp);
}

bool TemMesmaParidade(int a, int b) {
    if(a%2 == 1 && b%2 == 1)
        return true;
    else if (a%2 == 0 && b%2 == 0)
        return true;
    else return false;
}

void moveToStart(Stack* s) {
    s->curr = s->head;
}

void calculo_pilha(Stack* s) {
    int result;

    while((s->curr->next != s->tail) && (s->head->next != NULL)) {
        if(TemMesmaParidade(s->curr->next->element, s->curr->next->next->element)) {
            result = abs(s->curr->next->element - s->curr->next->next->element);
            remove_from_stack(s);
            remove_from_stack(s);

            if(result != 0)
                insert(s, result);
        }
        else return;
    }
}

void clear(Stack* s) {
    int i = 0, j = s->cnt;
    moveToStart(s);

    for(i = 0; i < j; i++)
        remove_from_stack(s);
}