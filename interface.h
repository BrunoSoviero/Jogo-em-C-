#ifndef INTERFACE_H
#define INTERFACE_H
#include "raylib.h"
#include <stdio.h>

#define FPS 60
#define TAMANHO_HORIZONTAL 800
#define TAMANHO_VERTICAL 600
#define NUM_FRAMES 3
#define MAPA_ALTURA 30
#define MAPA_LARGURA 30

typedef struct
{
    Texture2D texturaBotao;
    Rectangle limites;
    bool clicado;
} Botao; // define a estrutura dos botoes do menu

typedef struct
{
    Texture2D escada;
    Texture2D plataforma;
    Texture2D porta;
    Texture2D personagem;
    Texture2D monstro;
    Texture2D fundo;
    Texture2D coracao;
    Texture2D menina;
    Texture2D moeda;
    Texture2D molhado;
} TexturasJogo; // define as texturas do jogo

typedef struct
{
    Vector2 posicao;
    float velocidade;
    int vida;
    float pontuacao;
    float tempoUltimoMovimento;
    float tempoInicioPulo;
    bool estaPulando;
    float tempoEspecial;
    bool especial;
    float tempoUltimoPulo;
} Boneco;

typedef struct
{
    float x;
    float y;
    float velocidade;
    int direcao; // 1 = direita, -1 = esquerda
    Texture2D textura;
    float tempoUltimoMovimento;
    float delayMovimento;
} Monstro;

typedef struct tipo_placar
{
    char nome[20];
    float time;
} TIPO_PLACAR;

// Declaracao das funcoes

// Funcoes para o menu
// Inicializa e desenha o menu
int Menu(void);
// Inicializa o botao com as variaveis necessarias
void InitBotao(Botao *btn, const char *caminhoTextura, Vector2 pos, float scale);
// Libera a memoria do botao
void UnloadBotao(Botao *btn);
// Desenha um botao
void desenhaBotao(Botao *btn);
// Verifica se o botao esta pressionado
bool botaoPressionado(Vector2 mousePos, Botao *btn, bool mousePressionado);
// Cria o menu de pausa
int MenuPausa(void);
// Funcao pra reniciar a fase
void reiniciaFase(char m[MAPA_ALTURA][MAPA_LARGURA], Boneco *bombeiro, int faseAtual);
// Funcoes para desenhar os mapas
void desenhaMapa(TexturasJogo text, char m[MAPA_ALTURA][MAPA_LARGURA], Boneco *bombeiro);
void carregaMapa(const char *caminhoArquivo, char m[MAPA_ALTURA][MAPA_LARGURA], Boneco *bombeiro);
void desenhaCoracao(TexturasJogo text, Boneco bombeiro);

// Funcoes para o placar
void RegistraPlacar(TIPO_PLACAR placar[], float tempo, FILE *arq);
void desenhaPlacarNaTela(TIPO_PLACAR placar[]);

// Funcoes para desenhar as telas de vutoria e derrota
int desenhaVitoria(void);
int desenhaDerrota(void);

#endif