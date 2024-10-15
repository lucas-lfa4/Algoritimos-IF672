#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Link {
    char* element;
    struct Link* next;
} Link;

typedef struct {
    Link* top;
    int size;
} Stack;

typedef struct {
    Link* front;
    Link* rear;
    int size;
} Queue;

Link* create_link(char* it, Link* nextval);
Stack* create_stack(void);
void push(Stack* s, char* it);
void pop(Stack* s);
void clear(Stack* s);
void print_s(Stack* s);

Link* create_link_initial(Link* nextval);
Queue* create_queue(void);
void enqueue(Queue* q, char* it);
char* dequeue(Queue* q);
void clear_q(Queue* q);

int calc_vencedor(Stack* s, int N);

int main() {
    int N, i, n_partidas = 0;
    bool acabou = false;
    char linha[20];
    scanf("%d", &N);

    char cartas[N][3];
    Queue** fila_cartas = (Queue** ) calloc(N, sizeof(Queue*));
    Stack* cuscuz = create_stack();

    for(i = 0; i < N; i++)
        fila_cartas[i] = create_queue();

    while(!acabou) {
        scanf("%s", linha);

        if(strcmp(linha, "DEA") == 0) {
            for(i = 0; i < N; i++) {
                scanf("%s", cartas[i]);
                enqueue(fila_cartas[i], strdup(cartas[i]));
            }
        }
        else if(strcmp(linha, "RND") == 0) {
            clear(cuscuz);
            
            for(i = 0; i < N; i++) {
                push(cuscuz, dequeue(fila_cartas[i]));
            }

            printf("%d %d\n", n_partidas, N - calc_vencedor(cuscuz, N) - 1);
            n_partidas++;
        }
        else if(strcmp(linha, "PRT") == 0) {
            print_s(cuscuz);
        }
        else acabou = true;
    }

    for(i = 0; i < N; i++)
        clear_q(fila_cartas[i]);
    
    free(fila_cartas);
    free(cuscuz);

    return 0;
}

Link* create_link(char* it, Link* nextval) {
    Link* n = (Link* ) malloc(sizeof(Link));

    n->element = it;
    n->next = nextval;

    return n;
}

//Funcoes pilhas

Stack* create_stack(void) {
    Stack* s = (Stack* ) malloc(sizeof(Stack));

    s->top = NULL;
    s->size = 0;

    return s;
}

void push(Stack* s, char* it) {
    s->top = create_link(it, s->top);
    s->size++;
}

void pop(Stack* s) {
    if(s->top == NULL) { return; }

    Link* tmp = s->top;

    s->top = s->top->next;
    s->size--;

    free(tmp->element);
    free(tmp);
}

void clear(Stack* s) {
    int i = 0, j = s->size;

    while(i < j) {
        pop(s);
        i++;
    }
}

void print_s(Stack* s) {
    Link* curr = s->top;

    while(curr != NULL) {
        if(curr->next == NULL) {
            printf("%s", curr->element);
        }
        else printf("%s ", curr->element);
        
        curr = curr->next;
    }
    printf("\n");
}

//Funcoes filas

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

void enqueue(Queue* q, char* it) {
    q->rear->next = create_link(it, NULL);
    q->rear = q->rear->next;
    q->size++;
}

char* dequeue(Queue* q) {
    if(q->size == 0) { return NULL; }

    Link* aRemover = q->front->next;
    char* it = q->front->next->element;

    q->front->next = q->front->next->next;
    if(q->front->next == NULL) {
        q->rear = q->front;
    }
    q->size--;

    
    free(aRemover);

    return it;
}

void clear_q(Queue* q) {
    int i = 0, j = q->size;

    while(i < j) {
        dequeue(q);
        i++;
    }
}

int calc_vencedor(Stack* s, int N) {
    int pos_vencedor = 0, pos_curr = 1;
    char* vencedor = s->top->element;
    bool empate = false;
    Link* curr = s->top->next;

    while(curr != NULL) {
        if(vencedor[0] < curr->element[0]) {
            if(empate)
                empate = false;
            
            vencedor = curr->element;
            pos_vencedor = pos_curr;
        }
        else if(vencedor[0] == curr->element[0]) {
            if(vencedor[1] < curr->element[1]) {
                if(empate)
                    empate = false;

                vencedor = curr->element;
                pos_vencedor = pos_curr;
            }
            else if(vencedor[1] == curr->element[1])
                empate = true;
        }

        curr = curr->next;
        pos_curr++;
    }

    if(empate)
        return N;
    else
        return pos_vencedor;
}