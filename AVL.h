#include <stdio.h>
#include <stdlib.h>

typedef int E;
typedef int Key;

const E ERRO = -1; //valor padrao de erro

typedef struct BSTNode {
    Key key;
    E element;
    struct BSTNode* left;
    struct BSTNode* right;
    int height;
} BSTNode;

typedef struct {
    BSTNode* root;
    int nodeCount;
} BST;

BSTNode* create_BSTNode(Key k, E e) {
    BSTNode* n = (BSTNode* ) malloc(sizeof(BSTNode));

    n->key = k;
    n->element = e;
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

E findHelp(BSTNode* rt, Key k) {
    if(rt == NULL) {
        printf("Essa chave n existe\n");
        return ERRO;
    }

    if(rt->key > k) 
        return findHelp(rt->left, k);
    else if(rt->key == k)
        return rt->element;
    else 
        return findHelp(rt->right, k);
}

E find(BST* bst, Key k) {
    return findHelp(bst->root, k);
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

BSTNode* insertHelp(BSTNode* rt, Key k, E e) {
    if(rt == NULL) 
        return create_BSTNode(k, e);

    if(rt->key > k)
        rt->left = insertHelp(rt->left, k, e);
    else
        rt->right = insertHelp(rt->right, k, e);

    rt->height = 1 + max(h(rt->left), h(rt->right));
    int balance = getBalance(rt);

    if(balance < -1 && k >= rt->right->key) return leftRotate(rt);
    if(balance > 1 && k < rt->left->key) return rightRotate(rt);
    if(balance > 1 && k >= rt->left->key) {
        rt->left = leftRotate(rt->left);
        return rightRotate(rt);
    }
    if(balance < -1 && k < rt->right->key) {
        rt->right = rightRotate(rt->right);
        return leftRotate(rt);
    }

    return rt;
}

void insert(BST* bst, Key k, E e) {
    bst->root = insertHelp(bst->root, k, e);
    bst->nodeCount++;
}

BSTNode* getMin(BSTNode* rt) {
    if(rt->left == NULL)
        return rt;
    
    return getMin(rt->left);
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

BSTNode* removeHelp(BSTNode* rt, Key k) {
    if(rt == NULL)
        return NULL;

    if(rt->key > k)
        rt->left = removeHelp(rt->left, k);
    else if(rt->key < k)
        rt->right = removeHelp(rt->right, k);
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
            rt->element = tmp->element;
            rt->key = tmp->key;
            rt->right = deleteMin(rt->right);
        }
    }

    //Rotacoes e balanceamento
    rt->height = 1 + max(h(rt->left), h(rt->right));
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

E remove_from_bst(BST* bst, Key k) {
    E tmp = findHelp(bst->root, k);

    if(tmp != -1) {
        bst->root = removeHelp(bst->root, k);
        bst->nodeCount--;
    }

    return tmp;
}

BSTNode* paiDe(BST* bst, BSTNode* rt) {
    BSTNode* curr = bst->root;

    if(bst->root == rt) return NULL;

    while(!(curr->left == rt || curr->right == rt)) {
        if(curr->key > rt->key) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    return curr;
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

void pre_ordem_print(BSTNode* rt) {
    if(rt != NULL) {
        printf("Chave %d, elemento %d\n", rt->key, rt->element);
        pre_ordem_print(rt->left);
        pre_ordem_print(rt->right);
    }
}

void em_ordem_print(BSTNode* rt) {
    if(rt != NULL) {
        em_ordem_print(rt->left);
        printf("Chave %d, elemento %d\n", rt->key, rt->element);
        em_ordem_print(rt->right);
    }
}

void pos_ordem_print(BSTNode* rt) {
    if(rt != NULL) {
        pos_ordem_print(rt->left);
        pos_ordem_print(rt->right);
        printf("Chave %d, elemento %d\n", rt->key, rt->element);
    }
}