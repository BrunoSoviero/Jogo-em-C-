#include "raylib.h"
#include "jogo.h"
#include <stdio.h>

/*Cria um menu de opções para comecar o jogo*/
void Menu(void)
{
    InitWindow(TAMANHO_HORIZONTAL, TAMANHO_VERTICAL, "Jogo Final");
    SetTargetFPS(FPS);

    // Carrega a textura do fundo do menu
    Image imgFundo = LoadImage("graficos/background.png");
    ImageResize(&imgFundo, TAMANHO_HORIZONTAL, TAMANHO_VERTICAL);

    Texture2D background = LoadTextureFromImage(imgFundo);

    Botao botaoStart, botaoScore, botaoExit;
    float centroX = TAMANHO_HORIZONTAL / 3.0f; 
    float escalaTela = (float)TAMANHO_HORIZONTAL/ 800.0f; // pega o valor do tamanho da tela e divide por 800 (valor original da tela)
    // Inicializacao dos botoes do menu
    InitBotao(&botaoStart, "graficos/start.png", (Vector2){ centroX, TAMANHO_VERTICAL * 0.30f }, escalaTela);
    InitBotao(&botaoScore, "graficos/score.png", (Vector2){ centroX, TAMANHO_VERTICAL * 0.50f }, escalaTela);
    InitBotao(&botaoExit,  "graficos/exit.png",  (Vector2){ centroX, TAMANHO_VERTICAL * 0.70f }, escalaTela);
     bool sair = false;

    while(WindowShouldClose() == false && sair == false)
    {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        if(botaoPressionado(mousePosition, &botaoStart, mousePressed)){
            printf("StartButtonPressed");
        }
        if(botaoPressionado(mousePosition, &botaoScore, mousePressed)){
            printf("StartButtonPressed");
        }
        if(botaoPressionado(mousePosition, &botaoExit, mousePressed)){
            sair = true;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE); // Desenha o fundo
        desenhaBotao(&botaoStart); 
        desenhaBotao(&botaoScore);
        desenhaBotao(&botaoExit);
        EndDrawing();
    }
    UnloadBotao(&botaoStart);
    UnloadBotao(&botaoScore);
    UnloadBotao(&botaoExit);
    UnloadImage(imgFundo);
    CloseWindow();
}

int main(){
    Menu();
    return 0;
}

void InitBotao(Botao* btn, const char* caminhoTextura, Vector2 pos, float scale)
{
    Image img = LoadImage(caminhoTextura);
    
    int novaLargura = (int)(img.width * scale);
    int novaAltura = (int)(img.height * scale);

    ImageResize(&img, novaLargura, novaAltura);

    btn->texturaBotao = LoadTextureFromImage(img);
    UnloadImage(img);

    // Define a área de clique (largura total e altura de apenas 1 frame)
    btn->limites.x = pos.x;
    btn->limites.y = pos.y;
    btn->limites.width = (float)btn->texturaBotao.width;
    btn->limites.height = (float)btn->texturaBotao.height / NUM_FRAMES;
    
    btn->clicado = false;
}

void UnloadBotao(Botao* btn)
{
    UnloadTexture(btn->texturaBotao);
}

void desenhaBotao(Botao* btn)
{
    Vector2 mousePos = GetMousePosition();
    Color corBotao = WHITE; // Cor normal

    if (CheckCollisionPointRec(mousePos, btn->limites))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) corBotao = GRAY; // Clicado
        else corBotao = LIGHTGRAY; 
    }

    // Desenha a textura inteira, mas aplica o filtro de cor selecionado
    DrawTexture(btn->texturaBotao, btn->limites.x, btn->limites.y, corBotao);
} 

bool botaoPressionado(Vector2 mousePos, Botao* btn, bool mousePressionado){
    Rectangle rect = {btn->limites.x, btn->limites.y, (float)btn->texturaBotao.width, (float)btn->texturaBotao.height};

    if (CheckCollisionPointRec(mousePos, rect) && mousePressionado){

        return true;

    }

    else    

        return false;

}