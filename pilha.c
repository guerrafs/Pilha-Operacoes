/**
 * @file pilha.c
 * @author Fabricio Guerra (f.guerra@aluno.ifsp.edu.br)
 * @brief training
 * @version 0.1
 * @date 2022-11-23
 * @copyright Copyright (c) 2022
 */
#include <stdlib.h>
#include <stdio.h>

typedef struct Pilha
{
    int info;
    int TamPilha;
    struct Pilha *prox;
} Pilha;

typedef struct Cont
{
    int TamPilha1;
    int TamPilha2;
} Cont;

void menu(void)
{
    printf("1- Inserir na Pilha 1.\n");
    printf("2- Transferir um elemento da Pilha 1 para a Pilha 2.\n");
    printf("3- Transferir toda a Pilha 1 para a Pilha 2.\n");
    printf("4- Inserir na Pilha 2.\n");
    printf("5- Transferir um elemento da Pilha 2 para a Pilha 1.\n");
    printf("6- Transferir toda a Pilha 2 para a Pilha 1.\n");
    printf("7- Exibir as duas Pilhas.\n");
    printf("8- Remover da Pilha 1.\n");
    printf("9- Remover da Pilha 2.\n");
    printf("10- Sair.\n");
}

void push(Pilha **p, int v)
{
    Pilha *novo = (Pilha *)malloc(sizeof(Pilha));
    novo->info = v;
    novo->prox = *p;
    *p = novo;
}

int pop(Pilha **p)
{
    int v;
    Pilha *aux;
    if ((*p) == NULL)
    {
        printf("Pilha vazia.\n");
        exit(1);
    }
    aux = *p;
    v = (*p)->info;
    *p = (*p)->prox;
    free(aux);
    return v;
}

int PilhaVazia(Pilha *p)
{
    if (p == NULL)
        return 1;
    return 0;
}

void Imprime(Pilha *A, Pilha *B, Cont *cont)
{
    Pilha *a = A;
    Pilha *b = B;
    int aux;

    system("cls");
    if (cont->TamPilha1 > cont->TamPilha2)
    {
        aux = cont->TamPilha1 - cont->TamPilha2;
        for (; aux > 0; aux--)
        {
            printf("   %d\n", a->info);
            a = a->prox;
        }
    }
    if (cont->TamPilha2 > cont->TamPilha1)
    {
        aux = cont->TamPilha2 - cont->TamPilha1;
        for (; aux > 0; aux--)
        {
            printf("   \t   %d\n", b->info);
            b = b->prox;
        }
    }

    while (a != NULL && b != NULL)
    {
        printf("   %d\t   %d\n", a->info, b->info);
        a = a->prox;
        b = b->prox;
    }
    printf("-------\t-------\n");
    printf("Pilha 1\tPilha 2.\n");
    system("Pause");
    system("CLS");
}

void Liberar(Pilha *A, Pilha *B)
{
    Pilha *a = A;
    Pilha *b = B;
    Pilha *Aux;
    while (a != NULL)
    {
        Aux = a->prox;
        free(a);
        a = Aux;
    }
    while (b != NULL)
    {
        Aux = b->prox;
        free(b);
        b = Aux;
    }
}

int main()
{
    Pilha *A = NULL;
    Pilha *B = NULL;
    Cont *contador = (Cont *)malloc(sizeof(Cont));
    contador->TamPilha1 = 0;
    contador->TamPilha2 = 0;
    int op, valor;

    do
    {
        menu();
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\nDigite um valor:");
            scanf("%d", &valor);
            push(&A, valor);
            contador->TamPilha1++;
            break;
        case 2:
            if (!PilhaVazia(A))
            {
                push(&B, pop(&A));
                contador->TamPilha1--;
                contador->TamPilha2++;
                break;
            }
            printf("\nPilha Vazia\n");
            break;
        case 3:
            if (!PilhaVazia(A))
            {
                while (A != NULL)
                {
                    push(&B, pop(&A));
                }
                contador->TamPilha2 = contador->TamPilha1 + contador->TamPilha2;
                contador->TamPilha1 = 0;
                break;
            }
            printf("\nPilha Vazia\n");
            break;
        case 4:
            printf("\nDigite um valor:");
            scanf("%d", &valor);
            push(&B, valor);
            contador->TamPilha2++;
            break;
        case 5:
            if (!PilhaVazia(B))
            {
                push(&A, pop(&B));
                contador->TamPilha2--;
                contador->TamPilha1++;
                break;
            }
            printf("\nPilha Vazia\n");
            break;
        case 6:
            if (!PilhaVazia(B))
            {
                while (B != NULL)
                {
                    push(&A, pop(&B));
                }
                contador->TamPilha1 = contador->TamPilha2 + contador->TamPilha1;
                contador->TamPilha2 = 0;
                break;
            }
            printf("\nPilha Vazia\n");
            break;

        case 7:
            if (!(PilhaVazia(A) && PilhaVazia(B)))
                Imprime(A, B, contador);
            printf("\nPilhas vazias.\n");
            break;
        case 8:
            if (!PilhaVazia(A))
            {
                pop(&A);
                contador->TamPilha1--;
                break;
            }
            printf("\nPilha Vazia\n");
            break;
        case 9:
            if (!PilhaVazia(B))
            {
                pop(&B);
                contador->TamPilha2--;
                break;
            }
            printf("\nPilha Vazia\n");
            break;
        case 10:
            break;
        default:
            printf("\nOpcao invalida.\n");
            break;
        }
    } while (op != 10);

    Liberar(A, B);

    return 0;
}