#ifndef LISTA_CIRCULAR_H
#define LISTA_CIRCULAR_H

typedef enum {
    VAZIO = 0,
    CARRO = 1,
    CAMINHAO = 2,
    MOTO = 3
} TipoElemento;

typedef struct No {
    TipoElemento dado;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int tamanho;
} ListaCircular;

ListaCircular *criar_lista(void);
void destruir_lista(ListaCircular *lista);
int adicionar_no(ListaCircular *lista, TipoElemento dado);
void mover_ponteiro(ListaCircular *lista);
TipoElemento informacao_posicao(const ListaCircular *lista, int n);

#endif
