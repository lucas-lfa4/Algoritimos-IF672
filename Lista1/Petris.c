#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Structs para as pilhas
typedef struct Link {
    int element;
    struct Link* next;
} Link;

typedef struct {
    Link* top;
    int size;
} Stack;


// Struct para as listas de pilhas
typedef struct Link_l {
    Stack* element;
    struct Link_l* next;
} Link_l;

typedef struct {
    Link_l* head;
    Link_l* tail;
    Link_l* curr;
    int cnt;
} List;

// Funcoes para a pilha
Link* create_link_pilha(int it, Link* nextVal);
Stack* create_stack(void);
void push(Stack* s, int it);
void pop(Stack* s);
int topValue(Stack* s);
void clear(Stack* s);
bool isEmpty(Stack* s);
void print_s(Stack* s);


// Funcoes para a lista de pilhas
Link_l* create_link_lista(Stack* it, Link_l* nextVal);
Link_l* create_link_lista_inicial(Link_l* nextVal);
List* create_list(void);
void insert(List* l, Stack* it);
void moveToStart(List* l);
void moveToTail(List* l);
void prev(List* l);
void next(List* l);
void moveToPos(List* l, int pos);
void remove_from_list(List* l);
Stack* getValue(List* l);
void clear_l(List* l);


int main() {
    int N, i, coluna, cor;
    bool acabou = false;
    char linha[20];
    scanf("%d", &N);

    List** listas = (List** ) calloc(N, sizeof(List*));

    for(i = 0; i < N; i++) {
        listas[i] = create_list();
    }

    for(i = 0; i < N; i++, acabou = false) {
        while(!acabou) {
            scanf("%s",linha);
            if(strcmp(linha, "END") == 0)
                acabou = true;
            else {
                sscanf(linha, "%d", &coluna);
                scanf("%d", &cor);
                if(coluna == listas[i]->cnt + 1) {
                    //adiciona um novo elemento de lista de pilhas no final da lista
                    moveToTail(listas[i]);

                    insert(listas[i], create_stack());
                    push(listas[i]->tail->element, cor);
                }
                else if(coluna == 0) {
                    //adiciona um novo elemento de lista de pilhas no inicio da lista
                    moveToStart(listas[i]);

                    insert(listas[i], create_stack());
                    push(listas[i]->head->next->element, cor);
                }
                else {
                    //coloca a cor na coluna indicada
                    moveToPos(listas[i], coluna);
                    if(cor == topValue(listas[i]->curr->element)) {
                        pop(listas[i]->curr->element);

                        //se a pilha for vazia, deletar ela da lista de pilhas

                        if(isEmpty(listas[i]->curr->element)) {
                            prev(listas[i]);
                            remove_from_list(listas[i]);
                        }
                    }
                    else {
                        push(listas[i]->curr->element, cor);
                    }
                }
            }
        }
        
    }

    
    for(i = 0; i < N; i++) {
        moveToStart(listas[i]);
        printf("caso %d:", i);
        while(listas[i]->curr != listas[i]->tail) {
            printf(" %d", topValue(listas[i]->curr->next->element));
            next(listas[i]);
        }
        printf("\n");
    }

    for(i = 0; i < N; i++) {
        moveToStart(listas[i]);
        while(listas[i]->curr != listas[i]->tail) {
            clear(listas[i]->curr->next->element);
            next(listas[i]);
        }
        clear_l(listas[i]);
    }

    free(listas);

    return 0;
}

// Funcoes para a pilha:

Link* create_link_pilha(int it, Link* nextval) {
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
    s->top = create_link_pilha(it, s->top);
    s->size++;
}

void pop(Stack* s) {
    if(s->top == NULL) { return; }

    Link* tmp = s->top;

    s->top = s->top->next;
    s->size--;

    free(tmp);
}

int topValue(Stack* s) {
    if(s->top == NULL) {
        printf("A pilha nap tem elementos\n");
        return 0;
    }
    else return s->top->element;
}

void clear(Stack* s) {
    int i = 0, j = s->size;

    while(i < j) {
        pop(s);
        i++;
    }
}

bool isEmpty(Stack* s) {
    if(s->top == NULL) { return true; }
    else { return false; }
}

void print_s(Stack* s) {
    Link* curr = s->top;

    while(curr != NULL) {
        printf("%d ", curr->element);
        
        curr = curr->next;
    }
    printf("\n");
}

// Funcoes para a lista de pilhas:

Link_l* create_link_lista(Stack* it, Link_l* nextVal) {
    Link_l* n = (Link_l* ) malloc(sizeof(Link_l));

    n->element = it;
    n->next = nextVal;

    return n;
}

Link_l* create_link_lista_inicial(Link_l* nextVal) {
    Link_l* n = (Link_l* ) malloc(sizeof(Link_l));

    n->next = nextVal;

    return n;
}

List* create_list(void) {
    List* l = (List* ) malloc(sizeof(List));

    l->curr = create_link_lista_inicial(NULL);
    l->tail = l->curr;
    l->head = l->curr;
    l->cnt = 0;

    return l;
}

void insert(List* l, Stack* it) {
    l->curr->next = create_link_lista(it, l->curr->next);

    if(l->tail == l->curr) {
        l->tail = l->curr->next;
    }

    l->cnt++;
}

void moveToStart(List* l) {
    l->curr = l->head;
}

void moveToTail(List* l) {
    l->curr = l->tail;
}

void prev(List* l) {
    if(l->curr == l->head) { return; }

    Link_l* tmp = l->head;

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

void moveToPos(List* l, int pos) {
    int i = 0;
    moveToStart(l);

    for(i = 0; i < pos; i++)
        next(l);
}

void remove_from_list(List* l) {
    if(l->curr->next == NULL) { return; }

    Link_l* removido = l->curr->next;

    if(l->tail == l->curr->next) {
        l->tail = l->curr;
    }

    l->curr->next = l->curr->next->next;
    l->cnt--;

    clear(removido->element);
    free(removido);
}

Stack* getValue(List* l) {
    return l->curr->element;
}

void clear_l(List* l) {
    int i = 0, j = l->cnt;
    moveToStart(l);

    for(i = 0; i < j; i++)
        remove_from_list(l);
}