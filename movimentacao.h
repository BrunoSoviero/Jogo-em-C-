#ifndef MOVIMENTACAO_H
#define MOVIMENTACAO_H

#include "interface.h"

int movimentoPersonagem(char m[MAPA_ALTURA][MAPA_LARGURA], Boneco *bombeiro);

void initMonstro(Monstro monstros[], int* numMonstros, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho);
void movimentoMonstro(Monstro* monstro, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho);
int verificaColisaoMonstro(char m[MAPA_ALTURA][MAPA_LARGURA], Monstro* monstro, float blocoTamanho, Boneco *b);
void desenhaMonstro(Monstro* monstro, TexturasJogo texturas, float blocoTamanho, float comecoMapa);
void atualizaMonstro(Monstro* monstro, char m[MAPA_ALTURA][MAPA_LARGURA], TexturasJogo texturas, Boneco *b);

#endif