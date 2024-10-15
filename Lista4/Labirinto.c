#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define UNVISITED 0
#define VISITED 1

#define NORTE 0
#define OESTE 1
#define SUL 2
#define LESTE 3


typedef struct {
    int linha;
    int coluna;
} Pos;

typedef struct Link {
    Pos element;
    struct Link* next;
} Link;

typedef struct {
    Link* front;
    Link* rear;
    int size;
} Queue;

Link* create_link(Pos it, Link* nextval);
Link* create_link_initial(Link* nextval);
Queue* create_queue(void);
void enqueue(Queue* q, Pos it);
Pos dequeue(Queue* q);
Pos next(int** matriz, Pos v, int direcao, Pos limites);
Pos first(int** matriz, Pos v, Pos limites);
void setMark(int** mark, Pos pos, int mk);
int getMark(int** mark, Pos pos);
void marcarAntecessor(Pos** antecessores, Pos filho, Pos pai);

int main() {
    int i, j;
    Pos start;
    Pos finish;
    Pos v, w;
    int M, N;
    int** matriz;
    int** Mark;
    Pos** matriz_antecessores;
    int direcao;
    bool achou = false;
    int movimentos = 0;
    Pos curr;

    scanf("%d %d", &M, &N);

    matriz = (int** ) calloc(M, sizeof(int*));
    if(matriz == NULL) {
        printf("Erro na alocacao da matriz\n");
        exit(1);
    }

    Mark = (int** ) calloc(M, sizeof(int*));
    if(Mark == NULL) {
        printf("Erro na alocacao do Mark\n");
        exit(1);
    }

    matriz_antecessores = (Pos** ) calloc(M, sizeof(Pos*));
    if(matriz_antecessores == NULL) {
        printf("Erro na alocacao da matriz de antecessores\n");
    }

    for(i = 0; i < M; i++) {
        matriz[i] = (int* ) calloc(N, sizeof(int));
        if(matriz[i] == NULL) {
            printf("Erro na alocacao da matriz[%d]\n", i);
            exit(1);
        }

        Mark[i] = (int* ) calloc(N, sizeof(int));
        if(Mark[i] == NULL) {
            printf("Erro na alocacao do Mark[%d]\n", i);
            exit(1);
        }

        matriz_antecessores[i] = (Pos* ) calloc(N, sizeof(Pos));
        if(matriz_antecessores[i] == NULL) {
            printf("Erro na alocacao de matriz_antecessores[%d]\n", i);
            exit(1);
        }
    }
    
    Pos limites;
    limites.coluna = N;
    limites.linha = M;

    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            scanf("%d", &matriz[i][j]);

            if(matriz[i][j] == 2) {
                start.linha = i;
                start.coluna = j;
            }

            if(matriz[i][j] == 3) {
                finish.linha = i;
                finish.coluna = j;
            }

            Mark[i][j] = UNVISITED;

            matriz_antecessores[i][j].coluna = -1;
            matriz_antecessores[i][j].linha = -1;
        }
    }

    Queue* q = create_queue();
    enqueue(q, start);
    setMark(Mark, start, VISITED);

    while(q->size > 0 && !achou) {
        v = dequeue(q);
        w = first(matriz, v, limites);
        direcao = NORTE;

        while(w.coluna != -1 && w.linha != -1 && !achou) {
            marcarAntecessor(matriz_antecessores, w, v);

            if(getMark(Mark, w) == UNVISITED) {
                enqueue(q, w);
                setMark(Mark, w, VISITED);
                
                if(w.linha == finish.linha && w.coluna == finish.coluna) {
                    achou = true;
                }
            }

            direcao++;
            w = next(matriz, v, direcao, limites);
        }
    }

    if(achou) {
        curr = finish;

        while(!(curr.linha == start.linha && curr.coluna == start.coluna)) {
            curr = matriz_antecessores[curr.linha][curr.coluna];
            movimentos++;
        }

        printf("%d\n", movimentos);
    }
    else
        printf("Labirinto Impossivel\n");

    for(i = 0; i < M; i++) {
        free(matriz[i]);
        free(Mark[i]);
    }
    free(matriz);
    free(Mark);

    return 0;
}

Link* create_link(Pos it, Link* nextval) {
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

void enqueue(Queue* q, Pos it) {
    q->rear->next = create_link(it, NULL);
    q->rear = q->rear->next;
    q->size++;
}

Pos dequeue(Queue* q) {
    Link* removido;
    Pos it;

    if(q->size == 0) {
        printf("Nao tem o que remover\n");
        it.linha = -1;
        it.coluna = -1;
        return it;
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

Pos next(int** matriz, Pos v, int direcao, Pos limites) {
    Pos pos;
    pos.coluna = -1;
    pos.linha = -1;

    if(direcao == NORTE) {
        if(v.linha <= 0) {
            direcao++;
        }
        else {
            if(matriz[v.linha - 1][v.coluna] == 1) {
                direcao++;
            }
            else {
                pos.linha = v.linha - 1;
                pos.coluna = v.coluna;
                return pos;
            }
        }
    }
    if(direcao == OESTE) {
        if(v.coluna <= 0) {
            direcao++;
        }
        else {
            if(matriz[v.linha][v.coluna - 1] == 1) {
                direcao++;
            }
            else {
                pos.coluna = v.coluna - 1;
                pos.linha = v.linha;
                return pos;
            }
        }
    }
    if(direcao == SUL) {
        if(v.linha >= limites.linha - 1) {
            direcao++;
        }
        else {
            if(matriz[v.linha + 1][v.coluna] == 1) {
                direcao++;
            }
            else {
                pos.coluna = v.coluna;
                pos.linha = v.linha + 1;
                return pos;
            }
        }
    }
    if(direcao == LESTE) {
        if(v.coluna >= limites.coluna - 1) {
            return pos;
        }
        else {
            if(matriz[v.linha][v.coluna + 1] == 1) {
                return pos;
            }
            else {
                pos.coluna = v.coluna + 1;
                pos.linha = v.linha;
                return pos;
            }
        }
    }

    return pos;
}

Pos first(int** matriz, Pos v, Pos limites) {
    return next(matriz, v, NORTE, limites);
}

void setMark(int** mark, Pos pos, int mk) {
    mark[pos.linha][pos.coluna] = mk;
}

int getMark(int** mark, Pos pos) {
    return mark[pos.linha][pos.coluna];
}

void marcarAntecessor(Pos** antecessores, Pos filho, Pos pai) {
    if(antecessores[filho.linha][filho.coluna].linha == -1 && antecessores[filho.linha][filho.coluna].coluna == -1) {
        antecessores[filho.linha][filho.coluna].linha = pai.linha;
        antecessores[filho.linha][filho.coluna].coluna = pai.coluna;
    }
}