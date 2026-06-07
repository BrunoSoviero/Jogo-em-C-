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

    while (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { // Debug para a volta do menu pausa
        // equanto o mouse estiver abaixado, ele so desenha o menu sem verificar nenhum clique para nao pegar toques acidentais
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        desenhaBotao(&botaoStart);
        desenhaBotao(&botaoScore);
        desenhaBotao(&botaoExit);
        EndDrawing();
    }

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
    UnloadTexture(background);
    UnloadImage(imgFundo);
    CloseWindow();
    return 2;
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
                m[y][x] = '.'; 
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
int MenuPausa(void)
{
    // Carrega a textura do fundo do menu
    Image imgFundo = LoadImage("graficos/background.png");
    ImageResize(&imgFundo, TAMANHO_HORIZONTAL, TAMANHO_VERTICAL);

    Texture2D background = LoadTextureFromImage(imgFundo);

    Botao botaoContinue, botaoMenu, botaoExit;
    float centroX = TAMANHO_HORIZONTAL / 3.0f; 
    float escalaTela = (float)TAMANHO_HORIZONTAL/ 800.0f; // pega o valor do tamanho da tela e divide por 800 (valor original da tela)
    // Inicializacao dos botoes do menu
    InitBotao(&botaoContinue, "graficos/continue.png", (Vector2){ centroX, TAMANHO_VERTICAL * 0.30f }, escalaTela);
    InitBotao(&botaoMenu, "graficos/menu.png", (Vector2){ centroX, TAMANHO_VERTICAL * 0.50f }, escalaTela);
    InitBotao(&botaoExit,  "graficos/exit.png",  (Vector2){ centroX, TAMANHO_VERTICAL * 0.70f }, escalaTela);
     bool sair = false;

    while (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { // Debug para quando clicar para voltar para o menu o clique nao pegar no menu principal
    // enquanto o mouse estiver abaixado, ele so desenha o menu sem verificar nenhum clique para nao pegar toques acidentais
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        desenhaBotao(&botaoContinue);
        desenhaBotao(&botaoMenu);
        desenhaBotao(&botaoExit);
        EndDrawing();
    }

    while(WindowShouldClose() == false && sair == false)
    {
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT); // verfica se o mouse esta pressionado

        if(botaoPressionado(mousePosition, &botaoContinue, mousePressed)){
            printf("ContinueButtonPressed");
            UnloadBotao(&botaoContinue);
            UnloadBotao(&botaoMenu);
            UnloadBotao(&botaoExit);
            UnloadImage(imgFundo);
            return 0;
        }
        if(botaoPressionado(mousePosition, &botaoMenu, mousePressed)){
            printf("MenuButtonPressed");
            UnloadBotao(&botaoContinue);
            UnloadBotao(&botaoMenu);
            UnloadBotao(&botaoExit);
            UnloadImage(imgFundo);
            return 1;
        }
        if(botaoPressionado(mousePosition, &botaoExit, mousePressed)){
            UnloadBotao(&botaoContinue);
            UnloadBotao(&botaoMenu);
            UnloadBotao(&botaoExit);
            UnloadImage(imgFundo);
            return 2;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE); // Desenha o fundo
        desenhaBotao(&botaoContinue); 
        desenhaBotao(&botaoMenu);
        desenhaBotao(&botaoExit);
        // Isso vai desenhar uma linha vermelha exatamente onde o seu código acha que o botão está
        EndDrawing();
    }
    UnloadBotao(&botaoContinue);
    UnloadBotao(&botaoMenu);
    UnloadBotao(&botaoExit);
    UnloadTexture(background);
    UnloadImage(imgFundo);
    CloseWindow();
    return 2;
}

void RegistraPlacar(TIPO_PLACAR placar[], int tempoFinal, FILE *arq)
{
    char nome[20];
    if(tempoFinal < placar[9].time){ // verifica se o tempo do jogador é melhor que o ultimo colocado no placar
        printf("Digite seu nome: ");
        scanf("%s", nome);
    }
    else
    {
        return;
    }
    for(int i = 0; i < 10; i++)
    {
        if(tempoFinal < placar[i].time)
        { 
            for(int j = 9; j > i; j--)
            {
                placar[j] = placar[j-1];
            }
            strcpy(placar[i].nome, nome);  // copia o nome do jogador para a posição correta no placar
            placar[i].time = tempoFinal;
            break;
        }
    }
    rewind(arq); // volta para o inicio do arquivo para sobrescrever os placares antigos
    fwrite(placar, sizeof(TIPO_PLACAR), 10, arq); // escreve o placar atualizado no arquivo
}

void imprimePlacar(TIPO_PLACAR placar[]){
    for(int i = 0; i < 10; i++){
        if(placar[i].nome[0] != '\0'){
            printf("%d. %s - %d segundos\n", i+1, placar[i].nome, placar[i].time);
        }
    }
}

int desenhaVitoria(void){
     // Drena todos os frames enquanto ENTER estiver pressionado
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
        
        if (!IsKeyDown(KEY_ENTER))
            break; // Só sai quando ENTER estiver completamente solto
    }
    while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Você Ganhou!", MAPA_LARGURA/2 + 60, MAPA_ALTURA/2 + 200, 100, WHITE);
    DrawText("Pressione ENTER para continuar", MAPA_LARGURA/2 + 110, MAPA_ALTURA/2 + 300, 30, WHITE);
    EndDrawing();
    if(IsKeyPressed(KEY_ENTER)){

        return 1;
    }
}
    return 0;
}

int desenhaDerrota(void){
     // Drena todos os frames enquanto ENTER estiver pressionado
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
        
        if (!IsKeyDown(KEY_ENTER))
            break; // Só sai quando ENTER estiver completamente solto
    }
    while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Você Perdeu!", MAPA_LARGURA/2 + 60, MAPA_ALTURA/2 + 200, 100, WHITE);
    DrawText("Pressione ENTER para continuar", MAPA_LARGURA/2 + 110, MAPA_ALTURA/2 + 300, 30, WHITE);
    EndDrawing();
    if(IsKeyPressed(KEY_ENTER)){

        return 1;
    }
}
    return 0;
}