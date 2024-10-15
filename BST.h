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

BSTNode* insertHelp(BSTNode* rt, Key k, E e) {
    if(rt == NULL) 
        return create_BSTNode(k, e);

    if(rt->key > k)
        rt->left = insertHelp(rt->left, k, e);
    else
        rt->right = insertHelp(rt->right, k, e);

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