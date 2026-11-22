#ifndef INTERFACE_H
#define INTERFACE_H

#include "regras.h"

void limpar_tela(void);
void desenhar_jogo(const Jogo *jogo);
char capturar_input(void);
void exibir_tela_final(const Jogo *jogo);

#endif

