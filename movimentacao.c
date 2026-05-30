#include "movimentacao.h"

int movimentoPersonagem(char m[MAPA_ALTURA][MAPA_LARGURA], Boneco *bombeiro)
{

    float tempoAtual = GetTime();

    // TRAVA DE VELOCIDADE
    if (tempoAtual - bombeiro->tempoUltimoMovimento < bombeiro->velocidade){
        return 0;
    }
    int x = bombeiro->posicao.x;
    int y = bombeiro-> posicao.y;
    if (IsKeyDown('D') || IsKeyDown(KEY_RIGHT))
    {
        if (x + 1 < MAPA_LARGURA && (m[y + 1][x] == 'Z' || m[y + 1][x] == 'H') && (m[y + 1][x + 1] == 'H' || m[y + 1][x + 1] == 'Z'))
        {
            bombeiro->posicao.x = x + 1;
            bombeiro->tempoUltimoMovimento = tempoAtual;
            return 0;
        }
       
    }
    if (IsKeyDown('A') || IsKeyDown(KEY_LEFT))
    {
        if (x - 1 >= 0 && (m[y + 1][x] == 'Z' || m[y + 1][x] == 'H') && (m[y + 1][x - 1] == 'H' || m[y + 1][x - 1] == 'Z'))
        {
            bombeiro->posicao.x = x - 1;
            bombeiro->tempoUltimoMovimento = tempoAtual;
            return 0;
        }
    }
    if (IsKeyDown('W') || IsKeyDown(KEY_UP))
    {
        if (y - 1 >= 0)
        { // verifica se nao vai passar da borda
            if (m[y - 1][x] == 'S' || m[y - 1][x] == 'H' || m[y - 1][x] == 'D')
            { // verifica se o bloco de cima é uma escada pra deixar subir
                bombeiro->posicao.y = y - 1;
                bombeiro->tempoUltimoMovimento = tempoAtual;
                return 0;
            }
        }
    }
    if (IsKeyDown('S') || IsKeyDown(KEY_DOWN))
    {
        if (y + 1 < MAPA_ALTURA)
        { // verifica se nao vai passar da borda
            if ((m[y + 1][x] == 'H' || m[y + 1][x] == 'S'))
            { // verifica se o bloco de baixo é uma escada pra deixar descer
                bombeiro->posicao.y = y + 1;
                bombeiro->tempoUltimoMovimento = tempoAtual;
                return 0;
        }
    }
    }
    if (IsKeyPressed(KEY_ENTER)){
        if(m[y][x] == 'F'){
            return 1;
        }
    }
return 0;
}


    void initMonstro(Monstro monstros[], int* numMonstros, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho){ 
    *numMonstros = 0; 
    for(int i = 0; i < MAPA_ALTURA; i++){ // Percorre o mapa para encontrar os monstros
        for(int j = 0; j < MAPA_LARGURA; j++){ 
            if(m[i][j] == 'M'){ // Se encontrar um monstro, inicializa suas propriedades
                monstros[*numMonstros].velocidade = 1.0f;
                monstros[*numMonstros].direcao = 1;
                monstros[*numMonstros].textura = LoadTexture("graficos/monstro.png");
                monstros[*numMonstros].tempoUltimoMovimento = 0.0f;
                monstros[*numMonstros].delayMovimento = 0.2f;
                monstros[*numMonstros].x = j * blocoTamanho;
                monstros[*numMonstros].y = i * blocoTamanho;

                m[i][j] = '.';

                (*numMonstros)++; 
            }
        }
    }
}

void movimentoMonstro(Monstro* monstro, char m[MAPA_ALTURA][MAPA_LARGURA], float blocoTamanho){
    float tempoAtual = GetTime();
    if (tempoAtual - monstro->tempoUltimoMovimento < monstro->delayMovimento) { 
        return;
    }

    int gridX = (int)(monstro->x / blocoTamanho); 
    int gridY = (int)(monstro->y / blocoTamanho);

    // Verifica se o próximo movimento é possível
    if(monstro->direcao == 1){ // Movendo para a direita
        if(gridX + 1 < MAPA_LARGURA && (m[gridY + 1][gridX + 1] == 'Z' || m[gridY + 1][gridX + 1] == 'H')){ // Verifica se o bloco à direita abaixo é um chão ou uma escada
            monstro->x += monstro->velocidade * blocoTamanho; // Move para a direita
        } else {
            monstro->direcao = -1; // Muda de direção
        }
    } else { // Movendo para a esquerda
        if(gridX - 1 >= 0 && (m[gridY + 1][gridX - 1] == 'Z' || m[gridY + 1][gridX - 1] == 'H')){ // Verifica se o bloco à esquerda abaixo é um chão ou uma escada
            monstro->x -= monstro->velocidade * blocoTamanho; // Move para a esquerda
        } else {
            monstro->direcao = 1; // Muda de direção
        }
    }

    monstro->tempoUltimoMovimento = tempoAtual;
}

void desenhaMonstro(Monstro* monstro, TexturasJogo texturas, float blocoTamanho, float comecoMapa){
Rectangle origem = {0, 0, monstro->textura.width, monstro->textura.height};
Rectangle destino = {comecoMapa + monstro->x, monstro->y, blocoTamanho, blocoTamanho};
DrawTexturePro(monstro->textura, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
}

int verificaColisaoMonstro(char m[MAPA_ALTURA][MAPA_LARGURA], Monstro* monstro, float blocoTamanho, Boneco *b){
    for(int y = 0; y < MAPA_ALTURA; y++){
        for(int x = 0; x < MAPA_LARGURA; x++){
            if(y == b->posicao.y && x == b->posicao.x){
                int monstroGridX = (int)(monstro->x / blocoTamanho);
                int monstroGridY = (int)(monstro->y / blocoTamanho);
                if(monstroGridX == x && monstroGridY == y){
                    return 1; // Colisão detectada
                }
            }
        }
    }
    return 0; // Nenhuma colisão detectada
}

void atualizaMonstro(Monstro* monstro, char m[MAPA_ALTURA][MAPA_LARGURA], TexturasJogo texturas, Boneco *b){
    float blocoTamanhoH = (float)GetScreenHeight() / MAPA_ALTURA;
    float blocoTamanhoV = (float)GetScreenWidth()  / MAPA_LARGURA;
    float blocoTamanho  = (blocoTamanhoH < blocoTamanhoV) ? blocoTamanhoH : blocoTamanhoV;
    float comecoMapa = ((float)GetScreenWidth() - (MAPA_LARGURA * blocoTamanho)) / 2.0f;

    movimentoMonstro(monstro, m, blocoTamanho);
    desenhaMonstro(monstro, texturas, blocoTamanho, comecoMapa);
    if(verificaColisaoMonstro(m, monstro, blocoTamanho, b)){
        CloseWindow();
    }
}