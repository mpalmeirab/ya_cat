#include <stdio.h>
#include "regras.h"
#include "interface.h"

int main(void) {
    Jogo jogo;
    inicializar_jogo(&jogo, 4);

    if (jogo.estado != JOGANDO) {
        fprintf(stderr, "Erro: nao foi possivel inicializar o jogo.\n");
        finalizar_jogo(&jogo);
        return 1;
    }

    while (jogo.estado == JOGANDO) {
        desenhar_jogo(&jogo);
        char comando = capturar_input();
        if (comando == 'q' || comando == 'Q') break;

        mover_jogador(&jogo, comando);
        atualizar_pista(&jogo);
        atualizar_estado_jogo(&jogo);
    }

    exibir_tela_final(&jogo);
    finalizar_jogo(&jogo);
    return 0;
}
