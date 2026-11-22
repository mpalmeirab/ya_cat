#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void limpar_tela(void) {
#ifdef _WIN32
    (void)system("cls");
#else
    (void)system("clear");
#endif
}

void desenhar_jogo(const Jogo *jogo) {
    if (jogo == NULL) return;
    limpar_tela();
    printf("========================================\n");
    printf("                YA CAT                  \n");
    printf(" Vidas: %d | Controles: W A S D | Q sair\n", jogo->yuri.vidas);

    printf("CHEGADA: ");
    for (int x = 0; x < LARGURA_PISTA; x++)
        printf(jogo->yuri.y == jogo->num_faixas + 1 && jogo->yuri.x == x ? "G " : "B ");
    putchar('\n');

    for (int y = jogo->num_faixas; y >= 1; y--) {
        printf("RUA %d  : ", y);
        ListaCircular *faixa = jogo->faixas[y - 1].lista;
        for (int x = 0; x < LARGURA_PISTA; x++) {
            if (jogo->yuri.y == y && jogo->yuri.x == x) putchar('G'), putchar(' ');
            else putchar(informacao_posicao(faixa, x) == VAZIO ? '.' : 'C'), putchar(' ');
        }
        putchar('\n');
    }

    printf("INICIO : ");
    for (int x = 0; x < LARGURA_PISTA; x++)
        printf(jogo->yuri.y == 0 && jogo->yuri.x == x ? "G " : "_ ");
    printf("\n\n");
}

char capturar_input(void) {
    char comando;
    printf("Movimento (w/a/s/d) ou q para sair: ");
    if (scanf(" %c", &comando) != 1) return 'q';
    return comando;
}

void exibir_tela_final(const Jogo *jogo) {
    if (jogo == NULL) return;
    desenhar_jogo(jogo);
    if (jogo->estado == VITORIA)
        printf("PARABENS! Yuri Albert atravessou tudo e conquistou o banquete!\n");
    else if (jogo->estado == DERROTA)
        printf("FIM DE JOGO! Yuri Albert perdeu todas as 3 vidas.\n");
    else
        printf("Jogo encerrado pelo jogador.\n");
}

