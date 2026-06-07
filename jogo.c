#include "interface.h"
#include "movimentacao.h"
#include <stdio.h>
#include <string.h>

int main()
{
    InitWindow(TAMANHO_HORIZONTAL, TAMANHO_VERTICAL, "Jogo Final");
    SetTargetFPS(FPS);

    // Inicializa as texturas do jogo
    TexturasJogo texturas;
    texturas.escada = LoadTexture("graficos/escada.png");
    texturas.plataforma = LoadTexture("graficos/plataforma.png");
    texturas.porta = LoadTexture("graficos/porta.png");
    texturas.personagem = LoadTexture("graficos/personagem.png");
    texturas.monstro = LoadTexture("graficos/monstro.png");
    texturas.fundo = LoadTexture("graficos/fundo.png");
    
    // Inicializa as variaveis para o funcinamento do jogo
    int retornoMenu; 
    int retornoJogo = 0; 
    int voltouPausa = 0;
    char m[MAPA_ALTURA][MAPA_LARGURA];
    Boneco bombeiro;
    bombeiro.posicao.x = 0;
    bombeiro.posicao.y = 0;
    bombeiro.velocidade = 0.15f;

    Monstro monstros[10];
    int numMonstros = 0;
   
    int fimDeJogo = 0;
    int faseAtual = 1;

    int retornoPausa = 0;
    float blocoTamanhoH = (float)GetScreenHeight() / MAPA_ALTURA;
    float blocoTamanhoV = (float)GetScreenWidth()  / MAPA_LARGURA;
    float blocoTamanho  = (blocoTamanhoH < blocoTamanhoV) ? blocoTamanhoH : blocoTamanhoV;

    int tempoInicio, tempoFinal;
    TIPO_PLACAR placar[10];  
    FILE *arq = fopen("placar.bin", "rb+"); 

     if (arq == NULL) 
     {
        arq = fopen("placar.bin", "wb+"); // cria o arquivo se não existir
        if (arq == NULL) {
            printf("Erro ao criar o arquivo de placar.\n");
            return 1;
        }
    }

    for (int i = 0; i < 10; i++) 
    {
        placar[i].time = 9999; // Inicializa os tempos como 0
        strcpy(placar[i].nome, ""); // Inicializa os nomes como string vazia
    }
    fread(placar, sizeof(TIPO_PLACAR), 10, arq); // Lê os placares existentes do arquivo
    imprimePlacar(placar); // Imprime o placar atual no console

    while(!WindowShouldClose())
    {
        
        if(!voltouPausa){
        retornoMenu = Menu();
        }
        else {
            voltouPausa = 0;
            continue; // ← pula o switch e volta pro topo do while, chamando Menu() na próxima iteração
        }
        voltouPausa = 0;
        
        if(retornoMenu == 2) // Se retornar 2 é para fechar o jogo
        {
            break;
        }

        switch(retornoMenu)
        {
            case 0: // Se o botão de iniciar for pressionado começa o jogo
            // atribui os valores iniciais para as variáveis do jogo
            fimDeJogo = 0;
            faseAtual = 1;
            retornoJogo = 0;
            bombeiro.posicao.x = 0;
            bombeiro.posicao.y = 0;
            bombeiro.velocidade = 0.15f;
            carregaMapa("mapas/Mapa1.txt", m, &bombeiro);
            initMonstro(monstros, &numMonstros, m, blocoTamanho);
            tempoInicio = GetTime(); // Inicia o tempo do jogo

            while(retornoJogo == 0 && !fimDeJogo) // Loop do jogo
            {
                retornoJogo = movimentoPersonagem(m, &bombeiro);
                if (retornoJogo == 1) // passou de fase
                {
                    if (faseAtual == 1)
                    {
                        // avança para mapa 2
                        carregaMapa("mapas/Mapa2.txt", m, &bombeiro);
                        initMonstro(monstros, &numMonstros, m, blocoTamanho);
                        faseAtual = 2; 
                        retornoJogo = 0; // reset pra continuar jogando no mesmo loop
                    }
                    else if (faseAtual == 2)
                    {
                        carregaMapa("mapas/Mapa3.txt", m, &bombeiro);
                        initMonstro(monstros, &numMonstros, m, blocoTamanho);
                        faseAtual = 3; 
                        retornoJogo = 0; // reseta de novo para continuar no loop
                    }
                    else if (faseAtual == 3)  
                    {
                        // Se venceu o mapa 3 (que agora é o último), vitória total!
                        printf("Parabens! Voce fechou o jogo inteiro!\n");
                        fimDeJogo = 1;
                        tempoFinal = GetTime() - tempoInicio; // Calcula o tempo total do jogo
                    }
                }
            }
            if(faseAtual == 3 && fimDeJogo)
            {   
                CloseWindow();
                RegistraPlacar(placar, tempoFinal, arq);
                imprimePlacar(placar);
                fclose(arq);
                return 0;
            }
            fclose(arq);
            break;
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
        if (IsKeyPressed(KEY_TAB) || IsKeyPressed(KEY_P)) 
        {
            retornoPausa = MenuPausa();
            if(retornoPausa == 0)
            {
                continue; // Volta para o jogo
            } else if(retornoPausa == 1){
                voltouPausa = 1;
                retornoJogo = -1;
                break; // Volta para o menu
                } else if(retornoPausa == 2){
                    CloseWindow(); // Sai do jogo    
                    return 0;
                }
        }
    }
    // Desenha o mapa e o monstro atualizado
    BeginDrawing();
    ClearBackground(BLACK);
    desenhaMapa(texturas, m, &bombeiro);
    for(int k = 0; k < numMonstros; k++)
    {
        atualizaMonstro(&monstros[k], m, texturas, &bombeiro);
    }
    EndDrawing();           
    break;
    default:
    break;
        
    UnloadTexture(texturas.escada);
    UnloadTexture(texturas.plataforma);
    UnloadTexture(texturas.porta);
    UnloadTexture(texturas.personagem);
    UnloadTexture(texturas.monstro);
    CloseWindow();


    return 0;
}