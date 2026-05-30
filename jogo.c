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
    texturas.monstro = LoadTexture("graficos/monstro.png");
    texturas.fundo = LoadTexture("graficos/fundo.png");
    
    int retornoMenu;
    int retornoJogo = 0;
    char m[MAPA_ALTURA][MAPA_LARGURA];
    Boneco bombeiro;
    bombeiro.posicao.x = 0;
    bombeiro.posicao.y = 0;
    bombeiro.velocidade = 0.15f;

    Monstro monstros[10];
    int numMonstros = 0;
   
    int fimDeJogo = 0;
    int faseAtual = 1;
    

    retornoMenu = Menu();
    switch (retornoMenu)
    {
    case 0:
        carregaMapa("mapas/Mapa1.txt", m, &bombeiro);
        
        float blocoTamanhoH = (float)GetScreenHeight() / MAPA_ALTURA;
        float blocoTamanhoV = (float)GetScreenWidth()  / MAPA_LARGURA;
        float blocoTamanho  = (blocoTamanhoH < blocoTamanhoV) ? blocoTamanhoH : blocoTamanhoV;
        initMonstro(monstros, &numMonstros, m, blocoTamanho);

        while(!IsKeyPressed(KEY_ESCAPE) && retornoJogo == 0){
        retornoJogo = movimentoPersonagem(m, &bombeiro);

         if (retornoJogo == 1)
        {
            if (faseAtual == 1)
            {
                // Avança para o Mapa 2
                carregaMapa("mapas/Mapa2.txt", m, &bombeiro);
                initMonstro(monstros, &numMonstros, m, blocoTamanho);
                faseAtual = 2; 
                retornoJogo = 0; // Reseta para continuar jogando no mesmo loop
            }
            else if (faseAtual == 2)
            {
                carregaMapa("mapas/Mapa3.txt", m, &bombeiro);
                initMonstro(monstros, &numMonstros, m, blocoTamanho);
                faseAtual = 3; 
                retornoJogo = 0; // Reseta novamente para continuar no loop
            }
            else if (faseAtual == 3)
            {
                // Se venceu o mapa 3 (que agora é o último), vitória total!
                printf("Parabens! Voce fechou o jogo inteiro!\n");
                fimDeJogo = 1;
            }
        }
            // Se o jogador perdeu
            else if (retornoJogo == 2)
            {
                printf("Voce Perdeu!\n");
                fimDeJogo = 1; // Encerra o loop do jogo
            }

        if (!fimDeJogo)
        {
            desenhaMapa(texturas, m, &bombeiro);
            for(int k = 0; k < numMonstros; k++)
            {
                atualizaMonstro(&monstros[k], m, texturas, &bombeiro);
            } 
        }
    }
    break;
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
    UnloadTexture(texturas.monstro);
    CloseWindow();



}