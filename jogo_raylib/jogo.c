#include "interface.h"
#include "movimentacao.h"
#include <stdio.h>
#include <string.h>

int main(){
    InitWindow(TAMANHO_HORIZONTAL, TAMANHO_VERTICAL, "Jogo Final");
    SetTargetFPS(FPS);

    TexturasJogo texturas;
    texturas.escada = LoadTexture("graficos/escada.png");
    texturas.plataforma = LoadTexture("graficos/plataforma.png");
    texturas.porta = LoadTexture("graficos/porta.png");
    texturas.personagem = LoadTexture("graficos/personagem.png");

    int retorno = Menu();
    char m[MAPA_ALTURA][MAPA_LARGURA];
    switch (retorno)
    {
    case 0:
        carregaMapa("mapas/Mapa1.txt", m);

        while(!IsKeyPressed(KEY_ESCAPE)){
        movimentoPersonagem(m);
        desenhaMapa(texturas, m);
        }
        break;
    case 2:
        CloseWindow();
        break;
    default:
        break;
    }
    
    UnloadTexture(texturas.escada);
    UnloadTexture(texturas.plataforma);
    UnloadTexture(texturas.porta);
    UnloadTexture(texturas.personagem);
    CloseWindow();



}