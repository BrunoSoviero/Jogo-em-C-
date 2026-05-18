#define FPS 60
#define TAMANHO_HORIZONTAL 800
#define TAMANHO_VERTICAL 600
#define NUM_FRAMES 3
typedef struct
{
    Texture2D texturaBotao;
    Rectangle limites;
    bool clicado;
}Botao; // define a estrutura dos botoes do menu


//Declaracao das funcoes

// Inicializa o botao com as variaveis necessarias
void InitBotao(Botao* btn, const char* caminhoTextura, Vector2 pos, float scale);
// Libera a memoria do botao
void UnloadBotao(Botao* btn);
// Desenha um botao
void desenhaBotao(Botao* btn);
bool botaoPressionado(Vector2 mousePos, Botao* btn, bool mousePressionado);
