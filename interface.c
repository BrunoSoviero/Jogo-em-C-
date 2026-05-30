#include "interface.h" 
#include <stdio.h>
#include <string.h>

/*Cria um menu de opções para comecar o jogo*/
int Menu(void)
{
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
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT); // verfica se o mouse esta pressionado

        if(botaoPressionado(mousePosition, &botaoStart, mousePressed)){
            printf("StartButtonPressed");
            UnloadBotao(&botaoStart);
            UnloadBotao(&botaoScore);
            UnloadBotao(&botaoExit);
            UnloadImage(imgFundo);
            return 0;
        }
        if(botaoPressionado(mousePosition, &botaoScore, mousePressed)){
            printf("StartButtonPressed");
            UnloadBotao(&botaoStart);
            UnloadBotao(&botaoScore);
            UnloadBotao(&botaoExit);
            UnloadImage(imgFundo);
            return 1;
        }
        if(botaoPressionado(mousePosition, &botaoExit, mousePressed)){
            UnloadBotao(&botaoStart);
            UnloadBotao(&botaoScore);
            UnloadBotao(&botaoExit);
            UnloadImage(imgFundo);
            return 2;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE); // Desenha o fundo
        desenhaBotao(&botaoStart); 
        desenhaBotao(&botaoScore);
        desenhaBotao(&botaoExit);
        // Isso vai desenhar uma linha vermelha exatamente onde o seu código acha que o botão está
        EndDrawing();
    }
    UnloadBotao(&botaoStart);
    UnloadBotao(&botaoScore);
    UnloadBotao(&botaoExit);
    UnloadImage(imgFundo);
    CloseWindow();
}


// *** Cria o mapa para jogar o jogo
void desenhaMapa(TexturasJogo text, char m[MAPA_ALTURA][MAPA_LARGURA], Boneco* bombeiro){
    int i, j;
    int x, y;
        // pega o tamanho da tela pra ajustar o mapa
        float larguraTela = GetScreenWidth();
        float alturaTela = GetScreenHeight();
        // ajusta o bloco pro tamamnho da tela
        float blocoTamanhoH = alturaTela  / MAPA_ALTURA;
        float blocoTamanhoV = larguraTela / MAPA_LARGURA;
        float blocoTamanho  = (blocoTamanhoH < blocoTamanhoV) ? blocoTamanhoH : blocoTamanhoV;

        float comecoMapa = ((larguraTela - (MAPA_LARGURA * blocoTamanho))/ 2.0f); // remover o excesso pro mapa ficar um quadrado e dar espaco pro score e pra vida

        BeginDrawing();

        ClearBackground(BLACK);

        for (y = 0; y < MAPA_ALTURA; y++)
        {
            for (x = 0; x < MAPA_LARGURA; x++)
            {
                if (m[y][x] == 'Z') // Verifica se é uma plataforma e desenha a plataforma
                {
                    Rectangle origem = {0, 0, text.plataforma.width, text.plataforma.height}; // recorta o tamanho da imagem original
                    Rectangle destino = {comecoMapa + (x * blocoTamanho), y * blocoTamanho, blocoTamanho, blocoTamanho}; //posicao e o tamamnho que a imagem tera na tela
                    DrawTexturePro(text.plataforma, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
                }
                if (m[y][x] == 'H' || m[y][x] == 'S') // verifica se é uma escada e desenha a escada
                {
                    Rectangle origem = {0, 0, text.escada.width, text.escada.height};
                    Rectangle destino = {comecoMapa + (x * blocoTamanho), y * blocoTamanho, blocoTamanho, blocoTamanho};
                    DrawTexturePro(text.escada, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
                }
                if (m[y][x] == 'F') // verifica se é uma porta e desenha a escada
                {
                    Rectangle origem = {0, 0, text.porta.width, text.porta.height};
                    Rectangle destino = {comecoMapa + (x * blocoTamanho), y * blocoTamanho, blocoTamanho, blocoTamanho};
                    DrawTexturePro(text.porta, origem, destino, (Vector2){0, 0}, 0.0f, WHITE);
                }
                
            }
        }

     Rectangle origemP = {0, 0, text.personagem.width, text.personagem.height};
    Rectangle destinoP = {
        comecoMapa + (bombeiro->posicao.x * blocoTamanho), 
        bombeiro->posicao.y * blocoTamanho, 
        blocoTamanho, 
        blocoTamanho
    };
    DrawTexturePro(text.personagem, origemP, destinoP, (Vector2){0, 0}, 0.0f, WHITE);

    EndDrawing();
    

}

void carregaMapa(const char* caminhoArquivo, char m[MAPA_ALTURA][MAPA_LARGURA], Boneco *bombeiro){
    
    FILE *arquivo = fopen(caminhoArquivo, "r");

    char buffer[256]; 
    for (int i = 0; i < MAPA_ALTURA; i++) // LE O MAPA TXT
    {
        if(fgets(buffer, sizeof(buffer), arquivo) == NULL) break;
        
        // Remove \n e \r
        buffer[strcspn(buffer, "\r\n")] = '\0';
        
        // Copia só os primeiros MAPA_LARGURA caracteres pro mapa
        strncpy(m[i], buffer, MAPA_LARGURA);
        m[i][MAPA_LARGURA - 1] = '\0'; // garante terminação
    }
    
    for (int y = 0; y < MAPA_ALTURA; y++) {
    for (int x = 0; x < MAPA_LARGURA; x++) {
        if (m[y][x] == 'P') {
            bombeiro->posicao.x = x;
            bombeiro->posicao.y = y;
            m[y][x] = '.'; // Tira o 'P' da matriz, mapa agora só tem o cenário.
            printf("P encontrado em x=%d y=%d\n", x, y);
        }
    }
}
    fclose(arquivo);
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
    btn->limites.height = (float)btn->texturaBotao.height;
    
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
