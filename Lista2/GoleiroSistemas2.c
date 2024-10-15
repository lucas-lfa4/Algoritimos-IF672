#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define COUNT 10

//profundidade = altura da raiz - altura atual

int total = 0;

typedef struct BSTNode {
    int id;
    int WEI;
    int RNK;
    struct BSTNode* left;
    struct BSTNode* right;
    int height;
} BSTNode;

typedef struct {
    BSTNode* root;
    int nodeCount;
} BST;

BSTNode* create_BSTNode(int id, int wei);
BST* create_BST(void);
BSTNode* findHelp(BSTNode* rt, int id);
BSTNode* find(BST* bst, int id);
int max(int a, int b);
int h(BSTNode* rt);
int getBalance(BSTNode* rt);
int somaDosWeis(BSTNode* rt);
BSTNode* leftRotate(BSTNode* rt);
BSTNode* rightRotate(BSTNode* rt);
BSTNode* insertHelp(BST* bst, BSTNode* rt, int id, int wei);
void insert(BST* bst, int id, int wei);
BSTNode* getMin(BSTNode* rt);
BSTNode* getMax(BSTNode* rt);
BSTNode* deleteMin(BSTNode* rt);
BSTNode* removeHelp(BST* bst, BSTNode* rt, int id);
void remove_from_bst(BST* bst, int id);
BSTNode* paiDe(BST* bst, BSTNode* rt);
BSTNode* antecessor(BST* bst, BSTNode* rt);
int profundidade(BSTNode* root, BSTNode* rt);

int main() {
    bool acabou = false;
    char linha[10];
    int X, W;
    BST* arvore = create_BST();
    BSTNode* elemento;

    while(!acabou) {
        scanf("%s", linha);

        if(strcmp(linha, "ADD") == 0) {
            scanf("%d %d", &X, &W);
            
            insert(arvore, X, W);

            printf("%d\n", total);
        }
        else if(strcmp(linha, "WEI") == 0) {
            scanf("%d", &X);
            elemento = find(arvore, X);
            if(elemento == NULL)
                printf("0 -1\n");
            else
                printf("%d %d\n", elemento->WEI, profundidade(arvore->root, elemento));
        }
        else if(strcmp(linha, "RNK") == 0) {
            scanf("%d", &X);
            elemento = find(arvore, X);
            if(elemento == NULL) {
                insert(arvore, X, 0);
                elemento = antecessor(arvore, find(arvore, X));
                int RNK = 0;
                BSTNode* aux = paiDe(arvore, elemento);
                while(aux != NULL) {
                    if(aux->id <= elemento->id)
                        RNK += aux->RNK + aux->WEI;
                    aux = paiDe(arvore, aux);
                }
                printf("%d\n", elemento->RNK + RNK + elemento->WEI);
                remove_from_bst(arvore, X);
            }
            else {
                int RNK = 0;
                BSTNode* aux = paiDe(arvore, elemento);
                while(aux != NULL) {
                    if(aux->id <= elemento->id)
                        RNK += aux->RNK + aux->WEI;
                    aux = paiDe(arvore, aux);
                }
                printf("%d\n", elemento->RNK + RNK);
            }
        }
        else if(strcmp(linha, "END") == 0)
            acabou = true;
    }

    return 0;
}

BSTNode* create_BSTNode(int id, int wei) {
    BSTNode* n = (BSTNode* ) malloc(sizeof(BSTNode));

    n->id = id;
    n->WEI = wei;
    n->RNK = 0;
    n->height = 0;
    n->left = NULL;
    n->right = NULL;

    total += wei;

    return n;
}

BST* create_BST(void) {
    BST* bst = (BST* ) malloc(sizeof(BST));

    bst->root = NULL;
    bst->nodeCount = 0;

    return bst;
}

BSTNode* findHelp(BSTNode* rt, int id) {
    if(rt == NULL)  return NULL;

    if(rt->id > id) 
        return findHelp(rt->left, id);
    else if(rt->id == id)
        return rt;
    else 
        return findHelp(rt->right, id);
}

BSTNode* find(BST* bst, int id) {
    return findHelp(bst->root, id);
}

int max(int a, int b) {
    if(a > b) return a;
    else return b;
}

int h(BSTNode* rt) {
    if(rt == NULL) return -1;

    return rt->height;
}

int getBalance(BSTNode* rt) {
    if(rt == NULL) return 0;

    return h(rt->left) - h(rt->right);
}

int somaDosWeis(BSTNode* rt) {
    if(rt == NULL)  return 0;

    return (rt->WEI + somaDosWeis(rt->left) + somaDosWeis(rt->right));
}

BSTNode* leftRotate(BSTNode* rt) {
    BSTNode* r = rt->right;
    BSTNode* rl = r->left;

    r->left = rt;
    rt->right = rl;

    rt->height = max(h(rt->left), h(rt->right)) + 1;
    r->height = max(h(r->left), h(r->right)) + 1;
    r->RNK = somaDosWeis(r->left);

    return r;
}

BSTNode* rightRotate(BSTNode* rt) {
    BSTNode* l = rt->left;
    BSTNode* lr = l->right;

    l->right = rt;
    rt->left = lr;

    rt->height = max(h(rt->left), h(rt->right)) + 1;
    rt->RNK = somaDosWeis(rt->left);
    l->height = max(h(l->left), h(l->right)) + 1;

    return l;  
}

BSTNode* insertHelp(BST* bst, BSTNode* rt, int id, int wei) {
    if(rt == NULL) 
        return create_BSTNode(id, wei);

    if(rt->id > id)
        rt->left = insertHelp(bst, rt->left, id, wei);
    else if(rt->id < id)
        rt->right = insertHelp(bst, rt->right, id, wei);
    else {
        rt->WEI += wei;
        total += wei;
        return rt;
    }


    //atualizacao das alturas e do RNK
    rt->height = 1 + max(h(rt->left), h(rt->right));
    rt->RNK = somaDosWeis(rt->left);
    
    //calculo do balance e possiveis rotacoes
    int balance = getBalance(rt);

    if(balance < -1 && id >= rt->right->id) return leftRotate(rt);
    if(balance > 1 && id < rt->left->id) return rightRotate(rt);
    if(balance > 1 && id >= rt->left->id) {
        rt->left = leftRotate(rt->left);
        return rightRotate(rt);
    }
    if(balance < -1 && id < rt->right->id) {
        rt->right = rightRotate(rt->right);
        return leftRotate(rt);
    }

    return rt;
}

void insert(BST* bst, int id, int wei) {
    bst->root = insertHelp(bst, bst->root, id, wei);
    bst->nodeCount++;
}

BSTNode* getMin(BSTNode* rt) {
    if(rt->left == NULL)
        return rt;
    
    return getMin(rt->left);
}

BSTNode* getMax(BSTNode* rt) {
    if(rt->right == NULL)
        return rt;
    
    return getMax(rt->right);
}

BSTNode* deleteMin(BSTNode* rt) {
    if(rt->left == NULL) {
        BSTNode* tmp = rt->right;
        free(rt);
        return tmp;
    }

    rt->left = deleteMin(rt->left);

    return rt;
}

BSTNode* removeHelp(BST* bst, BSTNode* rt, int id) {
    if(rt == NULL)
        return NULL;

    if(rt->id > id)
        rt->left = removeHelp(bst, rt->left, id);
    else if(rt->id < id)
        rt->right = removeHelp(bst, rt->right, id);
    else {
        if(rt->left == NULL) {
            BSTNode* tmp = rt->right;
            free(rt);
            return tmp;
        }
        else if(rt->right == NULL) {
            BSTNode* tmp = rt->left;
            free(rt);
            return tmp;
        }
        else {
            BSTNode* tmp = getMin(rt->right);
            rt->WEI = tmp->WEI;
            rt->id = tmp->id;
            rt->right = deleteMin(rt->right);
        }
    }

    //atualizacao das alturas e do RNK
    rt->height = 1 + max(h(rt->left), h(rt->right));
    rt->RNK = somaDosWeis(rt->left);

    //calculo do balance e possiveis rotacoes
    int balance = getBalance(rt);

    if(balance < -1) {
        if(getBalance(rt->right) < 1) return leftRotate(rt);
        else {
            rt->right = rightRotate(rt->right);
            return leftRotate(rt);
        }
    }
    if(balance > 1) {
        if(getBalance(rt->left) > 1) return rightRotate(rt);
        else {
            rt->left = leftRotate(rt->left);
            return rightRotate(rt);
        }
    }

    return rt;
}

void remove_from_bst(BST* bst, int id) {
    BSTNode* tmp = findHelp(bst->root, id);

    if(tmp != NULL) {
        bst->root = removeHelp(bst, bst->root, id);
        bst->nodeCount--;
    }
}

BSTNode* paiDe(BST* bst, BSTNode* rt) {
    BSTNode* curr = bst->root;

    if(bst->root == rt) return NULL;

    while(!(curr->left == rt || curr->right == rt)) {
        if(curr->id > rt->id) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return curr;
}

BSTNode* antecessor(BST* bst, BSTNode* rt) {
    if(rt == NULL)  return NULL;

    if(rt->left == NULL) {
        BSTNode* aux = paiDe(bst, rt);
        
        if(aux != NULL) {
            while(aux->id > rt->id) {
                aux = paiDe(bst, aux);
                if(aux == NULL) break;
            }
        }
        
        return aux;
    }
    else
        return getMax(rt->left);
}

int profundidade(BSTNode* root, BSTNode* rt) {
    int i = 0;
    BSTNode* aux = root;

    while(aux!= NULL && (aux->id != rt->id)) {
        if(aux->id > rt->id) {
            aux = aux->left;
            i++;
        }
        else {
            aux = aux->right;
            i++;
        }
    }

    return i;
}