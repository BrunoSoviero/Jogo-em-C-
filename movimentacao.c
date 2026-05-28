#include "movimentacao.h"

int movimentoPersonagem(char m[MAPA_ALTURA][MAPA_LARGURA],float* tempoUltimoMovimento, float* delayMovimento){
    Boneco bombeiro;
    float tempoAtual = GetTime();
    if (tempoAtual - *tempoUltimoMovimento < *delayMovimento) {
        return 0;
    }

    for (int y = 0; y < MAPA_ALTURA; y++){
        for(int x = 0; x < MAPA_LARGURA; x++){
            if (m[y][x] == 'P'){
                if (IsKeyDown ('D') || IsKeyDown(KEY_RIGHT)){
                    if (x+1 < MAPA_LARGURA && (m[y+1][x] == 'Z' || m[y+1][x] == 'H') && (m[y+1][x+1] == 'H' || m[y+1][x+1] == 'Z')){
                    char blocoAnterior = m[y][x+1];
                    bombeiro.posicao.x = x + 1;
                    m[y][x+1] = 'P';
                    m[y][x] = '.';
                    if(m[y+1][x] =='H'){
                        m[y][x] = 'D'; // Se o bloco de baixo é uma escada entao o bloco que tava era o D
                    }
                    else if(m[y-1][x] == 'H'){
                        m[y][x] = 'S'; // Se o bloco de cima é uma escada entao o bloco que tava era o S
                    }
                    if(blocoAnterior == 'F'){
                        return 1;
                    }
                    *tempoUltimoMovimento = tempoAtual;
                    return 0;
                    }
                    //1  Verifica se vai extrapolar os limites do mapa, 2 se embaixo e à direita é um vazio e se à direita nao é um chão para nao travar na escada, 3 se embaixo nao for uma escada ou uma psicao de subida e se em cima nao é uma escada ou um D  
                   // else if(x+1 >= MAPA_LARGURA || (m[y+1][x+1] == '.' && m[y][x+1] != 'Z') && ((m[y+1][x] != 'H' && m[y+1][x] != 'S') && (m[y-1][x] != 'H' && m[y-1][x] != 'D'))){
                     //  return 2;
                    //}
                }
                if (IsKeyDown ('A') || IsKeyDown(KEY_LEFT)){
                    if (x - 1 >= 0 && (m[y+1][x]== 'Z' || m[y+1][x] == 'H') && (m[y+1][x-1] == 'H' || m[y+1][x-1] == 'Z')){
                    bombeiro.posicao.x = x - 1;
                    m[y][x-1] = 'P';
                    m[y][x] = '.';
                    if(m[y+1][x] == 'H'){
                        m[y][x] = 'D';
                    }
                    else if(m[y-1][x] == 'H'){
                        m[y][x] = 'S';
                    }
                    *tempoUltimoMovimento = tempoAtual;
                    return 0;
                    }
                    //else if(x - 1 < 0 || (m[y+1][x-1] == '.' && m[y][x-1] != 'Z') && ((m[y+1][x] != 'H' && m[y+1][x] != 'S') && (m[y-1][x] != 'H' && m[y-1][x] != 'D'))){
                      //  return 2;
                    //}
                }
                if (IsKeyDown ('W') || IsKeyDown(KEY_UP)){
                    if(y - 1 >= 0){ // verifica se nao vai passar da borda
                    if (m[y - 1][x] == 'S' || m[y - 1][x] == 'H' || m[y-1][x] == 'D'){ // verifica se o bloco de cima é uma escada pra deixar subir
                    bombeiro.posicao.y = y - 1;
                    m[y-1][x] = 'P';
                    *tempoUltimoMovimento = tempoAtual;;
                    // se o bloco abaixo for uma escada redesenha ela
                    if(y+ 1 < MAPA_ALTURA && (m[y+1][x] == 'H' || m[y + 1][x] == 'S' || m[y+1][x] == 'Z' )){
                        
                        if(m[y+1][x] == 'Z'){ // se o bloco de baixo for chao, entao a posicao era a base da escada
                            m[y][x] = 'S';
                        }
                        else{ // se nao, era uma escada 
                           m[y][x] = 'H';
                        }
                        return 0;
                            }   
                        }    
                    }
                }
                if (IsKeyDown ('S') || IsKeyDown(KEY_DOWN)){
                    if(y + 1 < MAPA_ALTURA){ // verifica se nao vai passar da borda
                    char blocoDeBaixo = m[y+1][x];
                    if ((m[y+1][x] == 'H'||m[y+1][x] == 'S')) { // verifica se o bloco de cima é uma escada pra deixar subir
                    bombeiro.posicao.y = y - 1;
                    m[y+1][x] = 'P';
                    *tempoUltimoMovimento = tempoAtual;;
                    // se o bloco abaixo for uma escada redesenha ela
                    if(m[y-1][x] == '.' && blocoDeBaixo == 'H'){
                            m[y][x] = 'D';
                        }
                        else{ // se nao, era uma escada 
                           m[y][x] = 'H';
                        }
                        return 0;
                                }   
                            }    
                        }
                    }
                }
            }
            return 0;
    }



