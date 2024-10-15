#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
bool find(BNT* bnt, char* name);
int max(int a, int b);
int a(Node* rt);
int getBalance2(Node* rt);
Node* leftRotate2(Node* rt);
Node* rightRotate2(Node* rt);
Node* insertNameHelp(Node* rt, char* name);
void insertName(BNT* bnt, char* name);
void pre_ordem_print(Node* rt);

int main() {
    int i, n;
    char linha[10];
    BNT* arvore = createBNT();

    printf("Quantidade de nomes a inserir: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        scanf("%s", linha);
        printf("nome inserido: %s\n", linha);
        insertName(arvore, strdup(linha));
    }

    if(find(arvore, "LUCAS")) {
        printf("Tem sim\n");
    }

    pre_ordem_print(arvore->root);

    return 0;
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

bool find(BNT* bnt, char* name) {
    return findNameHelp(bnt->root, name);
}

int max(int a, int b) {
    if(a > b) return a;
    else return b;
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

void pre_ordem_print(Node* rt) {
    if(rt != NULL) {
        printf("%s\n", rt->name);
        pre_ordem_print(rt->left);
        pre_ordem_print(rt->right);
    }
}