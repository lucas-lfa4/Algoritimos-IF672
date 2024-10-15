#include "linked_list.h"

typedef struct Dictionary {
    int m;
    int cnt;
    List** H;
    int (*h) (int, int);
} Dictionary;

Dictionary* create_dict(int size, int (*funcao) (int, int)) {
    Dictionary* d = (Dictionary* ) malloc(sizeof(Dictionary));
    int i;

    d->m = size;
    d->H = (List** ) calloc(size, sizeof(List*));

    for(i = 0; i < size; i++)
        d->H[i] = create_list();

    d->h = funcao;
    
    return d;
}

Link* search(List* list, int k) {
    moveToStart(list);

    while(list->curr->next != NULL && list->curr->next->element <= k)
        next(list);

    if(list->curr == list->head)
        return NULL;
    else
        return list->curr;
}

Link* find(Dictionary* d, int k) {
    int pos = d->h(k, d->m);

    return search(d->H[pos], k);
}

void insert_dict(Dictionary* d, int k) {
    int pos;
    if(find(d, k) == NULL) {
        pos = d->h(k, d->m);
        moveToStart(d->H[pos]);
        while(d->H[pos]->curr->next != NULL && d->H[pos]->curr->next->element <= k)
            next(d->H[pos]);
        insert(d->H[pos], k);
    }
}