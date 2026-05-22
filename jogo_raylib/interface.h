#ifndef INTERFACE_H
#define INTERFACE_H
#include "raylib.h"

#define FPS 60
#define TAMANHO_HORIZONTAL 800
#define TAMANHO_VERTICAL 600
#define NUM_FRAMES 3
#define MAPA_ALTURA 30
#define MAPA_LARGURA 30

typedef struct{
    Texture2D texturaBotao;
    Rectangle limites;
    bool clicado;
}Botao; // define a estrutura dos botoes do menu

typedef struct{
    Texture2D escada;
    Texture2D plataforma;
    Texture2D porta;
    Texture2D personagem;
} TexturasJogo; // define as texturas do jogo

typedef struct{
    Vector2 posicao;
    int vida;
} Boneco; 

//Declaracao das funcoes

// Funcoes para o menu
// Inicializa e desenha o menu
int Menu(void);
// Inicializa o botao com as variaveis necessarias
void InitBotao(Botao* btn, const char* caminhoTextura, Vector2 pos, float scale);
// Libera a memoria do botao
void UnloadBotao(Botao* btn);
// Desenha um botao
void desenhaBotao(Botao* btn);
bool botaoPressionado(Vector2 mousePos, Botao* btn, bool mousePressionado);


// Funcoes para desenhar os mapas 
void desenhaMapa(TexturasJogo text, char m[MAPA_ALTURA][MAPA_LARGURA]);
void carregaMapa(const char* caminhoArquivo, char m[MAPA_ALTURA][MAPA_LARGURA]);
#endif