#include "movimentacao.h"

void movimentoPersonagem(char m[MAPA_LARGURA][MAPA_ALTURA],float* tempoUltimoMovimento, float* delayMovimento){
    Boneco bombeiro;
    float tempoAtual = GetTime();
    if (tempoAtual - *tempoUltimoMovimento >= *delayMovimento) {
    for (int y = 0; y < MAPA_LARGURA; y++){
        for(int x = 0; x < MAPA_ALTURA; x++){
            if (m[y][x] == 'P'){
                if (IsKeyDown ('D') || IsKeyDown(KEY_RIGHT)){
                    if (x+1 < MAPA_ALTURA){
                    bombeiro.posicao.x = x + 1;
                    m[y][x+1] = 'P';
                    m[y][x] = '.';
                    if(m[y+1][x] =='H'){
                        m[y][x] == 'D'; // Se o bloco de baixo é uma escada entao o bloco que tava era o D
                    }
                    else if(m[y-1][x] == 'H'){
                        m[y][x] = 'S'; // Se o bloco de cima é uma escada entao o bloco que tava era o S
                    }
                    *tempoUltimoMovimento = tempoAtual;
                    return;
                    }
                }
                if (IsKeyDown ('A') || IsKeyDown(KEY_LEFT)){
                    if (x - 1 >= 0){
                    bombeiro.posicao.x = x - 1;
                    m[y][x-1] = 'P';
                    m[y][x] = '.';
                    if(m[y+1][x] =='H'){
                        m[y][x] == 'D';
                    }
                    else if(m[y-1][x] == 'H'){
                        m[y][x] = 'S';
                    }
                    *tempoUltimoMovimento = tempoAtual;
                    return;
                    }
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
                        return;
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
                        return;
                            }   
                        }    
                    }
                }
            }
        }
    }
}

