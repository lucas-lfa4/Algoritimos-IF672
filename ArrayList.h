#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int maxSize;
    int listSize;
    int curr;
    int* listArray;
} List;

List* create_list(int size) {
    List* l = (List* ) malloc(sizeof(List));

    l->maxSize = size;
    l->listSize = 0;
    l->curr = 0;
    l->listArray = (int* ) calloc(size, sizeof(int));

    return l;
}

bool isFull(List* l) {
    if(l->listSize >= l->maxSize) {
        return true;
    }
    else return false;
}

bool isEmpty(List* l) {
    if(l->listSize <= 0) {
        return true;
    }
    else return false;
}

void clear(List* l) {
    free(l->listArray);


    l->listSize = 0;
    l->curr = 0;
    l->listArray = (int* ) calloc(l->maxSize, sizeof(int));
}

void append(List* l, int item) {
    if(l->listSize >= l->maxSize) {
        printf("Erro! Lista cheia\n");
        return;
    }

    int i = l->listSize;

    while(i > 0) {
        l->listArray[i] = l->listArray[i-1];
        i--;
    }

    l->listArray[0] = item;
    l->listSize++;
}

void insert(List* l, int it) {
    if(isFull(l)) {
        printf("Erro! Lista cheia\n");
        return;
    }

    int i = l->listSize;

    while(i > l->curr) {
        l->listArray[i] = l->listArray[i-1];
        i--;
    }

    l->listArray[l->curr] = it;
    l->listSize++;
}

void remove_from_list(List* l) {
    if(isEmpty(l)) {
        printf("Erro! A lista precisa ter pelo menos um elemento\n");
        return;
    }

    int i = l->curr;

    while(i < l->listSize) {
        l->listArray[i] = l->listArray[i+1];
        i++;
    }

    l->listSize--;
}

void moveToStart(List* l) {
    l->curr = 0;
}

void moveToEnd(List* l) {
    l->curr = l->listSize;
}

void prev(List* l) {
    if(l->curr != 0){
        l->curr--;
    }
}

void next_pos(List* l) {
    if(l->curr < l->listSize) {
        l->curr++;
    }
}

void moveToPos(List* l, int pos) {
    if(pos > 0 && pos < l->listSize)
        l->curr = pos;
    else printf("Posicao invalida\n");
}

int lenght(List* l) {
    return l->listSize;
}

int currPos(List* l) {
    return l->curr;
}

int getValue(List* l) {
    return l->listArray[l->curr];
}