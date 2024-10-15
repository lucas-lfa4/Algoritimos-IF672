#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//arvore que armazena o nome e os pontos de cada jogador
typedef struct BSTNode {
    int pontos;
    char* nome;
    struct BSTNode* left;
    struct BSTNode* right;
    int height;
} BSTNode;

typedef struct {
    BSTNode* root;
    int nodeCount;
} BST;

BSTNode* create_BSTNode(int p, char* nome);
BST* create_BST(void);
BSTNode* findHelp(BSTNode* rt, int p);
BSTNode* find(BST* bst, int p);
int max(int a, int b);
int h(BSTNode* rt);
int getBalance(BSTNode* rt);
BSTNode* leftRotate(BSTNode* rt);
BSTNode* rightRotate(BSTNode* rt);
BSTNode* insertHelp(BSTNode* rt, int p, char* nome);
void insert(BST* bst, int p, char* nome);
BSTNode* getMin(BSTNode* rt);
BSTNode* getMax(BSTNode* rt);
void clear_help(BSTNode* rt);
void clear(BST* bst);
BSTNode* paiDe(BST* bst, BSTNode* rt);//
BSTNode* sucessor(BST* bst, BSTNode* rt);//
BSTNode* antecessor(BST* bst, BSTNode* rt);//

//arvore para ve se tem algum nome repetido
typedef struct Node {
    char* name;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

typedef struct {
    Node* root;
    int nodeCount;
} BNT;

Node* createNode(char* name);
BNT* createBNT(void);
bool findNameHelp(Node* rt, char* name);
bool findName(BNT* bnt, char* name);
int a(Node* rt);
int getBalance2(Node* rt);
Node* leftRotate2(Node* rt);
Node* rightRotate2(Node* rt);
Node* insertNameHelp(Node* rt, char* name);
void insertName(BNT* bnt, char* name);
void pre_ordem_print_name(Node* rt);
void clear_help_name(Node* rt);
void clear_name(BNT* bst);

int main() {
    int k, i, p;
    char linha[20];
    char nome[10];

    BST* arvore = create_BST();
    BNT* arvore_nomes = createBNT();

    BSTNode* N;
    BSTNode* ANT;
    BSTNode* SUC;

    scanf("%d", &k);

    for(i = 0; i < k; i++) {
        scanf("%s", linha);

        if(strcmp(linha, "ADD") == 0) {
            scanf("%s %d", nome, &p);

            if(findName(arvore_nomes, nome))
                printf("%s ja esta no sistema.\n", nome);
            else {
                insertName(arvore_nomes, strdup(nome));
                insert(arvore, p, strdup(nome));
                printf("%s inserido com sucesso!\n", nome); 
            }
        }
        else if(strcmp(linha, "PROX") == 0) {
            scanf("%d", &p);
            //printf("Comando PROX com entrada %d\n", p);

            N = find(arvore, p);
            ANT = antecessor(arvore, N);
            SUC = sucessor(arvore, N);

            /*printf("nome: %s, pontos: %d\n", N->nome, N->pontos);
            printf("antecessor: %s, pontos: %d\n", ANT->nome, ANT->pontos);
            printf("sucessor: %s, pontos: %d\n", SUC->nome, SUC->pontos);*/

            if(ANT == NULL && SUC == NULL)
                printf("Apenas %s existe no sistema...\n", N->nome);
            else if(ANT == NULL)
                printf("%s e o menor! e logo apos vem %s\n", N->nome, SUC->nome);
            else if(SUC == NULL)
                printf("%s e o maior! e logo atras vem %s\n", N->nome, ANT->nome);
            else
                printf("%s vem apos %s e antes de %s\n", N->nome, ANT->nome, SUC->nome);

        }
    }


    clear(arvore);
    clear_name(arvore_nomes);

    return 0;
}

BSTNode* create_BSTNode(int p, char* nome) {
    BSTNode* n = (BSTNode* ) malloc(sizeof(BSTNode));

    n->pontos = p;
    n->nome = nome;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;

    return n;
}

BST* create_BST(void) {
    BST* bst = (BST* ) malloc(sizeof(BST));

    bst->root = NULL;
    bst->nodeCount = 0;

    return bst;
}

BSTNode* findHelp(BSTNode* rt, int p) {
    if(rt == NULL)  return NULL;

    if(rt->pontos > p) 
        return findHelp(rt->left, p);
    else if(rt->pontos == p)
        return rt;
    else 
        return findHelp(rt->right, p);
}

BSTNode* find(BST* bst, int p) {
    return findHelp(bst->root, p);
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

BSTNode* leftRotate(BSTNode* rt) {
    BSTNode* r = rt->right;
    BSTNode* rl = r->left;

    r->left = rt;
    rt->right = rl;

    rt->height = max(h(rt->left), h(rt->right)) + 1;
    r->height = max(h(r->left), h(r->right)) + 1;

    return r;
}

BSTNode* rightRotate(BSTNode* rt) {
    BSTNode* l = rt->left;
    BSTNode* lr = l->right;

    l->right = rt;
    rt->left = lr;

    rt->height = max(h(rt->left), h(rt->right)) + 1;
    l->height = max(h(l->left), h(l->right)) + 1;

    return l;  
}

BSTNode* insertHelp(BSTNode* rt, int p, char* nome) {
    if(rt == NULL) 
        return create_BSTNode(p, nome);

    if(rt->pontos > p)
        rt->left = insertHelp(rt->left, p, nome);
    else
        rt->right = insertHelp(rt->right, p, nome);

    rt->height = 1 + max(h(rt->left), h(rt->right));
    int balance = getBalance(rt);

    if(balance < -1 && p >= rt->right->pontos) return leftRotate(rt);
    if(balance > 1 && p < rt->left->pontos) return rightRotate(rt);
    if(balance > 1 && p >= rt->left->pontos) {
        rt->left = leftRotate(rt->left);
        return rightRotate(rt);
    }
    if(balance < -1 && p < rt->right->pontos) {
        rt->right = rightRotate(rt->right);
        return leftRotate(rt);
    }

    return rt;
}

void insert(BST* bst, int p, char* nome) {
    bst->root = insertHelp(bst->root, p, nome);
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

void clear_help(BSTNode* rt) {
    if(rt != NULL) {
        clear_help(rt->left);
        clear_help(rt->right);
        free(rt);
    }
}

void clear(BST* bst) {
    clear_help(bst->root);
    free(bst);
}

BSTNode* paiDe(BST* bst, BSTNode* rt) {
    BSTNode* curr = bst->root;

    if(bst->root == rt) return NULL;

    while(!(curr->left == rt || curr->right == rt)) {
        if(curr->pontos > rt->pontos) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return curr;
}

BSTNode* sucessor(BST* bst, BSTNode* rt) {
    if(rt == NULL)  return NULL;

    if(rt->right == NULL) {
        BSTNode* aux = paiDe(bst, rt);

        if(aux != NULL) {
            while(aux->pontos < rt->pontos){
                aux = paiDe(bst, aux);
                if(aux == NULL) break;
            }
        }
        
        return aux;
    }
    else {
        return getMin(rt->right);
    }
}

BSTNode* antecessor(BST* bst, BSTNode* rt) {
    if(rt == NULL)  return NULL;

    if(rt->left == NULL) {
        BSTNode* aux = paiDe(bst, rt);
        
        if(aux != NULL) {
            while(aux->pontos > rt->pontos){
                aux = paiDe(bst, aux);
                if(aux == NULL) break;
            }
        }
        
        return aux;
    }
    else
        return getMax(rt->left);
}

Node* createNode(char* name) {
    Node* n = (Node* ) malloc(sizeof(Node));

    n->name = name;
    n->left = NULL;
    n->right = NULL;
    n->height = 0;

    return n;
}

BNT* createBNT(void) {
    BNT* bnt = (BNT* ) malloc(sizeof(BNT));

    bnt->root = NULL;
    bnt->nodeCount = 0;

    return bnt;
}

bool findNameHelp(Node* rt, char* name) {
    if(rt == NULL) return false;

    if(strcmp(rt->name, name) < 0) 
        return findNameHelp(rt->left, name);
    else if(strcmp(rt->name, name) == 0)
        return true;
    else
        return findNameHelp(rt->right, name);
}

bool findName(BNT* bnt, char* name) {
    return findNameHelp(bnt->root, name);
}

int a(Node* rt) {
    if(rt == NULL) return -1;

    return rt->height;
}

int getBalance2(Node* rt) {
    if(rt == NULL)  return 0;

    return a(rt->left) - a(rt->right);
}

Node* leftRotate2(Node* rt) {
    Node* r = rt->right;
    Node* rl = r->left;

    r->left = rt;
    rt->right = rl;

    rt->height = 1 + max(a(rt->left), a(rt->right));
    r->height = 1 + max(a(r->left), a(r->right));

    return r; 
}

Node* rightRotate2(Node* rt) {
    Node* l = rt->left;
    Node* lr = l->right;

    l->right = rt;
    rt->left = lr;

    rt->height = max(a(rt->left), a(rt->right)) + 1;
    l->height = max(a(l->left), a(l->right)) + 1;

    return l;  
}

Node* insertNameHelp(Node* rt, char* name) {
    if(rt == NULL)  return createNode(name);

    if(strcmp(rt->name, name) < 0)
        rt->left = insertNameHelp(rt->left, name);
    else
        rt->right = insertNameHelp(rt->right, name);


    //att da altura do no e calculo do balance
    rt->height = 1 + max(a(rt->left), a(rt->right));
    int balance = getBalance2(rt);

    //possiveis rotacoes
    if(balance < -1 && strcmp(rt->right->name, name) >= 0)  return leftRotate2(rt);
    if(balance > 1 && strcmp(rt->left->name, name) < 0) return rightRotate2(rt);
    if(balance > 1 && strcmp(rt->left->name, name) >= 0) {
        rt->left = leftRotate2(rt->left);
        return rightRotate2(rt);
    }
    if(balance < -1 && strcmp(rt->right->name, name) < 0) {
        rt->right = rightRotate2(rt->right);
        return leftRotate2(rt);
    }
    
    return rt;
}

void insertName(BNT* bnt, char* name) {
    bnt->root = insertNameHelp(bnt->root, name);
    bnt->nodeCount++;
}

void pre_ordem_print_name(Node* rt) {
    if(rt != NULL) {
        printf("%s\n", rt->name);
        pre_ordem_print_name(rt->left);
        pre_ordem_print_name(rt->right);
    }
}

void clear_help_name(Node* rt) {
    if(rt != NULL) {
        clear_help_name(rt->left);
        clear_help_name(rt->right);
        free(rt);
    }
}

void clear_name(BNT* bst) {
    clear_help_name(bst->root);
    free(bst);
}