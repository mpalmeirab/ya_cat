#ifndef REGRAS_H
#define REGRAS_H

#include "lista_circular.h"

#define LARGURA_PISTA 20
#define MAX_FAIXAS 5
#define VIDAS_INICIAIS 3

typedef enum{
    JOGANDO, 
    VITORIA,
    DERROTA
}Estadojogo; 

typedef enum{
    VIVO,
    EM_MOVIMENTO, 
    MORTO
}EstadoJogador; 

// Yuri albert 
typedef struct {
    int x; 
    int y; 
    int x_anterior; 
    int y_anterior; 
    int vidas; 
    EstadoJogador estado; 
}Jogador; 

typedef struct {
    ListaCircular *lista; 
    int velocidade; 
    int contador; 
}Faixa; 

typedef struct {
    Jogador yuri; 
    Faixa faixas[MAX_FAIXAS];
    int num_faixas;
    Estadojogo estado; 
}Jogo; 

void inicializar_jogo(Jogo *jogo, int num_faixas);
void finalizar_jogo(Jogo *jogo);
void mover_jogador(Jogo *jogo, char direcao); 
void atualizar_pista(Jogo *jogo);
int verificar_colisao(Jogo *jogo);
void atualizar_estado_jogo(Jogo *jogo);

#endif


