#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Doubly_linked_list.h"

int main() {
    int i, j;
    List* lista = create_list();


    printf("Bem vindo ao meu programa de Lista de vetor\n");

    while(i != 0) {
        printf("0-Sair do programa\n");
        printf("1-clear\n");
        printf("2-Inserir\n");
        printf("3-inserir no inicio da lista\n");
        printf("4-remover\n");
        printf("5-mover o cursor para o inicio\n");
        printf("6-mover o cursor para o final\n");
        printf("7-mover o  cursor uma casa para a esquerda\n");
        printf("8-mover o  cursor uma casa para a direita\n");
        printf("9-mover o  cursor uma casa especifica\n");
        printf("10-comprimento da lista\n");
        printf("11-posicao do cursor\n");
        printf("12-pegar valor\n");
        printf("Escolha uma operacao:\n");
        scanf("%d", &i);

        switch (i)
        {
        case 1:
            clear(lista);
            break;
        case 2:
            printf("valor que deseja inserir:");
            scanf("%d", &j);
            insert(lista, j);
            break;
        case 3:
            printf("valor que deseja inserir:");
            scanf("%d", &j);
            insert(lista, j);
            break;
        case 4:
            remove_from_list(lista);
            break;
        case 5:
            moveToStart(lista);
            break;
        case 6:
            moveToEnd(lista);
            break;
        case 7:
            prev(lista);
            break;
        case 8:
            next(lista);
            break;
        case 9:
            printf("qual casa deseja ir:");
            scanf("%d", &j);
            moveToPos(lista, j);
            break;
        case 10:
            printf("O tamanho da lista eh: %d\n", lenght(lista));
            break;
        case 11:
            currPos(lista);
            break;
        case 12:
            printf("Valor: %d\n", getValue(lista));
            break;
        default:
            printf("Operacao invalida, escolha outra\n");
            break;
        }
    }

    return 0;
}