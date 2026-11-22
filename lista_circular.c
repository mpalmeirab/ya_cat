#include <stdlib.h>
#include "lista_circular.h"

ListaCircular *criar_lista(void) {
    ListaCircular *lista = malloc(sizeof *lista);
    if (lista == NULL) return NULL;

    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
    return lista;
}

void destruir_lista(ListaCircular *lista) {
    if (lista == NULL) return;

    No *atual = lista->inicio;
    for (int i = 0; i < lista->tamanho && atual != NULL; i++) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int adicionar_no(ListaCircular *lista, TipoElemento dado) {
    if (lista == NULL) return 0;

    No *novo = malloc(sizeof *novo);
    if (novo == NULL) return 0;

    novo->dado = dado;
    if (lista->inicio == NULL) {
        novo->proximo = novo;
        lista->inicio = novo;
        lista->fim = novo;
    } else {
        novo->proximo = lista->inicio;
        lista->fim->proximo = novo;
        lista->fim = novo;
    }

    lista->tamanho++;
    return 1;
}

void mover_ponteiro(ListaCircular *lista) {
    if (lista == NULL || lista->inicio == NULL || lista->tamanho <= 1) return;

    lista->inicio = lista->inicio->proximo;
    lista->fim = lista->fim->proximo;
}

TipoElemento informacao_posicao(const ListaCircular *lista, int n) {
    if (lista == NULL || lista->inicio == NULL || lista->tamanho <= 0 || n < 0)
        return VAZIO;

    int passos = n % lista->tamanho;
    const No *atual = lista->inicio;
    for (int i = 0; i < passos; i++) atual = atual->proximo;
    return atual->dado;
}
