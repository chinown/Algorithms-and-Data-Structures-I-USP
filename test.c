#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct no {
    int chave;
    int valor;
    struct no *prox;
} no_t;

typedef struct {
    no_t *primeiro;
} lista_t;

/* Devolve o nó com a chave, ou NULL. Em *ant fica o nó depois do qual
   a chave está (ou deveria estar); NULL se for no início da lista. */
no_t* buscar(lista_t *l, int chave, no_t **ant) {
    *ant = NULL;
    no_t *atual = l->primeiro;
    while (atual && atual->chave < chave) {
        *ant = atual;
        atual = atual->prox;
    }
    if (atual && atual->chave == chave) return atual;
    return NULL;
}

bool definir(lista_t *l, int chave, int valor) {
    no_t *ant;
    no_t *no = buscar(l, chave, &ant);
    int anterior = no ? no->valor : 0;
    if (anterior == valor) return false;      /* nada mudou */

    if (no && valor != 0) {                   /* existe: só atualiza */
        no->valor = valor;
    } else if (!no) {                         /* não existe: insere depois de ant */
        no_t *novo = malloc(sizeof(no_t));
        novo->chave = chave;
        novo->valor = valor;
        if (ant) { novo->prox = ant->prox;    ant->prox = novo; }
        else     { novo->prox = l->primeiro;  l->primeiro = novo; }
    } else {                                  /* existe e valor == 0: remove */
        if (ant) ant->prox = no->prox;
        else     l->primeiro = no->prox;
        free(no);
    }
    return true;
}