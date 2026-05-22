#include "movimentacao.h"

void movimentoPersonagem(char m[MAPA_LARGURA][MAPA_ALTURA]){
    Boneco bombeiro;
    for (int y = 0; y < MAPA_LARGURA; y++){
        for(int x = 0; x < MAPA_ALTURA; x++){
            if (m[y][x] == 'P'){
                bombeiro.posicao.x = y;
                bombeiro.posicao.y = x;
                if (IsKeyPressed ('D') || IsKeyPressed(KEY_RIGHT)){
                    if (x+1 < MAPA_ALTURA){
                    bombeiro.posicao.x = x + 1;
                    m[y][x+1] = 'P';
                    m[y][x] = '.';
                    return;
                    }
                }
                if (IsKeyPressed ('A') || IsKeyPressed(KEY_LEFT)){
                    if (x - 1 >= 0 && m[y][x - 1] == '.'){
                    bombeiro.posicao.x = x - 1;
                    m[y][x-1] = 'P';
                    m[y][x] = '.';
                    return;
                    }
                }
                if (IsKeyPressed ('W') || IsKeyPressed(KEY_UP)){
                    if(y - 1 >= 0){ // verifica se nao vai passar da borda
                    if (m[y - 1][x] == 'S' || m[y - 1][x] == 'H' || m[y-1][x] == '.' || m[y-1][x] == 'D'){ // verifica se o bloco de cima é uma escada pra deixar subir
                    bombeiro.posicao.y = y + 1;
                    m[y-1][x] = 'P';
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
                if (IsKeyPressed ('S') || IsKeyPressed(KEY_DOWN)){
                    if (m[y][x] == 'D' || m[y][x] == 'H'){
                    bombeiro.posicao.y = y + 1;
                    m[y+1][x] = 'P';
                    return;
                    }
                }
            }
        }
    }
}
