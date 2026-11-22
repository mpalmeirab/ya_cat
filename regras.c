#include <stddef.h>
#include "regras.h"

static int popular_faixa(ListaCircular *lista, int espacamento) {
    if (lista == NULL || espacamento <= 0) return 0;

    for (int i = 0; i < LARGURA_PISTA; i++) {
        TipoElemento elemento = (i % espacamento == 0) ? CARRO : VAZIO;
        if (!adicionar_no(lista, elemento)) return 0;
    }
    return 1;
}

void inicializar_jogo(Jogo *jogo, int num_faixas) {
    if (jogo == NULL) return;

    /* Estado seguro caso a alocacao de alguma faixa falhe. */
    jogo->num_faixas = 0;
    jogo->estado = DERROTA;
    jogo->yuri.x = LARGURA_PISTA / 2;
    jogo->yuri.y = 0;
    jogo->yuri.x_anterior = jogo->yuri.x;
    jogo->yuri.y_anterior = jogo->yuri.y;
    jogo->yuri.vidas = VIDAS_INICIAIS;
    jogo->yuri.estado = VIVO;

    if (num_faixas < 1) num_faixas = 1;
    if (num_faixas > MAX_FAIXAS) num_faixas = MAX_FAIXAS;

    for (int i = 0; i < num_faixas; i++) {
        ListaCircular *lista = criar_lista();
        if (lista == NULL) {
            finalizar_jogo(jogo);
            return;
        }

        jogo->faixas[i].lista = lista;
        jogo->faixas[i].velocidade = (i % 3) + 1;
        jogo->faixas[i].contador = 0;
        jogo->num_faixas++;

        if (!popular_faixa(lista, 4 + (i % 2))) {
            finalizar_jogo(jogo);
            jogo->num_faixas = 0;
            return;
        }
    }

    jogo->estado = JOGANDO;
}

void finalizar_jogo(Jogo *jogo) {
    if (jogo == NULL) return;
    for (int i = 0; i < jogo->num_faixas; i++) {
        destruir_lista(jogo->faixas[i].lista);
        jogo->faixas[i].lista = NULL;
    }
    jogo->num_faixas = 0;
}

void mover_jogador(Jogo *jogo, char direcao) {
    if (jogo == NULL || jogo->estado != JOGANDO) return;

    jogo->yuri.x_anterior = jogo->yuri.x;
    jogo->yuri.y_anterior = jogo->yuri.y;

    switch (direcao) {
        case 'w': case 'W':
            if (jogo->yuri.y < jogo->num_faixas + 1) jogo->yuri.y++;
            break;
        case 's': case 'S':
            if (jogo->yuri.y > 0) jogo->yuri.y--;
            break;
        case 'a': case 'A':
            if (jogo->yuri.x > 0) jogo->yuri.x--;
            break;
        case 'd': case 'D':
            if (jogo->yuri.x < LARGURA_PISTA - 1) jogo->yuri.x++;
            break;
        default:
            break;
    }
}

void atualizar_pista(Jogo *jogo) {
    if (jogo == NULL || jogo->estado != JOGANDO) return;

    for (int i = 0; i < jogo->num_faixas; i++) {
        jogo->faixas[i].contador++;
        if (jogo->faixas[i].contador >= jogo->faixas[i].velocidade) {
            mover_ponteiro(jogo->faixas[i].lista);
            jogo->faixas[i].contador = 0;
        }
    }
}

int verificar_colisao(Jogo *jogo) {
    if (jogo == NULL || jogo->yuri.y <= 0 || jogo->yuri.y > jogo->num_faixas)
        return 0;

    ListaCircular *faixa = jogo->faixas[jogo->yuri.y - 1].lista;
    if (faixa == NULL) return 0;
    return informacao_posicao(faixa, jogo->yuri.x) != VAZIO;
}

void atualizar_estado_jogo(Jogo *jogo) {
    if (jogo == NULL || jogo->estado != JOGANDO) return;

    if (verificar_colisao(jogo)) {
        jogo->yuri.vidas--;
        if (jogo->yuri.vidas <= 0) {
            jogo->yuri.vidas = 0;
            jogo->yuri.estado = MORTO;
            jogo->estado = DERROTA;
            return;
        }

        jogo->yuri.x = jogo->yuri.x_anterior;
        jogo->yuri.y = jogo->yuri.y_anterior;
        if (verificar_colisao(jogo)) {
            jogo->yuri.x = LARGURA_PISTA / 2;
            jogo->yuri.y = 0;
        }
        jogo->yuri.estado = VIVO;
        return;
    }

    if (jogo->yuri.y == jogo->num_faixas + 1) {
        jogo->estado = VITORIA;
    } else {
        jogo->yuri.estado = VIVO;
    }
}

