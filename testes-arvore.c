#include "AVL.h"
#include <stdbool.h>

void menu(void);

int main() {
    int i, n;
    bool acabou = false;
    BST* arvore = create_BST();

    printf("Bem vindo ao programa de teste das arvores binarias!\n");
    menu();

    while(!acabou) {
        printf("Digite uma operacao: ");
        scanf("%d", &i);

        switch (i) {
        case 0:
            acabou = true;
            break;
        case 1:
            printf("Digite o numero que deseja inserir: ");
            scanf("%d", &n);
            insert(arvore, n, n);
            break;
        case 2:
            printf("Digite o numero que deseja remover: ");
            scanf("%d", &n);
            remove_from_bst(arvore, n);
            break;
        case 3:
            printf("Digite o elemento:");
            scanf("%d", &n);
            BSTNode* pai = paiDe(arvore, findHelp(arvore, n));
            printf("O pai eh: %d", pai->element);
            break;
        case 4:
            pre_ordem_print(arvore->root);
            break;
        case 5:
            em_ordem_print(arvore->root);
            break;
        case 6:
            pos_ordem_print(arvore->root);
            break;
        case 7:
            menu();
            break;
        default:
            printf("Operacao invalida\n");
            break;
        }
    }



    return 0;
}

void menu(void) {
    printf("Digite 0 para fechar o programa\n");
    printf("Digite 1 para inserir um valor\n");
    printf("Digite 2 para remover um valor\n");
    printf("Digite 3 para ver o pai de um elemento");
    printf("Digite 4 para printar todos os valores em pre-ordem\n");
    printf("Digite 5 para printar todos os valores em ordem\n");
    printf("Digite 6 para printar todos os valores em pos-ordem\n");
    printf("Digite 7 para aparecer esse menu novamente\n");
}