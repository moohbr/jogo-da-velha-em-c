// Declaração de Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX_TABULEIRO 3

void escreve(void);
void renderiza(void);
char ler_jogador(void);
int verifica_vitoria(void);
void joga(void);
void escrever_rank(char nome[4], int vitoria);
void organizar(int* pontuacao, char nomes[10][255], int tamanho);
void ranking();
int gerar_posicao(int coluna, int linha);
int verifica_vitoria_horizontal(void);
int verifica_vitoria_vertical(void);
int verifica_vitoria_diagonal(void);

// Variaveis Globais
char tabuleiro[TAMANHO_MAX_TABULEIRO][TAMANHO_MAX_TABULEIRO];
char jogador = ' ';

// Declaração de Funcoes
// Funcao que escreve no tabuleiro do jogo da velha
void escreve(void){
    int ocupado = 0;

    while(ocupado == 0){
        int posicao = 0;

        printf("Selecione uma posicao: \n");
        scanf("%i", &posicao);

        for(int i = 0; i < TAMANHO_MAX_TABULEIRO; i++){
            for(int j = 0; j < TAMANHO_MAX_TABULEIRO; j++){
                if(gerar_posicao(i, j) == posicao){
                    if(tabuleiro[i][j] == 'X' || tabuleiro[i][j] == 'O'){
                        printf("Posição ocupada. Por favor, escolha outra.\n");
                    }else{
                        if(tabuleiro[i][j] == posicao + '0'){
                           tabuleiro[i][j]= jogador;

                           ocupado = 1;
                        }
                    }
                }
            }
        }
    }
}

// Funcao que renderiza o tabuleiro.
void renderiza(void){
    for(int i = 0; i < TAMANHO_MAX_TABULEIRO; i++){
        for(int j = 0; j < TAMANHO_MAX_TABULEIRO; j++){
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Funcao que ler o cada jogador é ( X ou O)
char ler_jogador(void){
    while (!(jogador == 'X' || jogador == 'O')){
        scanf("%c", &jogador);

        if(jogador == 'x'){
            jogador = 'X';    
        }

        if(jogador == 'o'){
            jogador = 'O';
        }

        if (!(jogador == 'X' || jogador == 'O')){
            printf("Selecione um caractere valido.\n");
        }
    }

      return jogador;
}

// Funcao que verifica se algum jogador ja ganhou
int verifica_vitoria(void){
    int venceu = 0 ;
    
    int vencedor_horizontal = verifica_vitoria_horizontal();
    int vencedor_vertical = verifica_vitoria_vertical();
    int vencedor_diagonal = verifica_vitoria_diagonal();

    if(vencedor_horizontal != 0 || vencedor_vertical != 0 || vencedor_diagonal != 0){
        if(vencedor_horizontal != 0) {
            venceu = vencedor_horizontal;
        }else if(vencedor_vertical != 0){
            venceu = vencedor_vertical;
        }else if(vencedor_diagonal != 0){
            venceu = vencedor_diagonal;
        }
    }

    return venceu;
}

// Funcao que inverte a variavel jogador e simplifica a escrita de varias funcoes
void joga(void){
    if (jogador == 'O'){
        jogador = 'X';
    }else {
        jogador = 'O';
    }

    escreve();
    renderiza();
}

// Funcao que escreve no arquivo de dados
void escrever_rank(char nome[4], int vitoria){
    FILE *f  = fopen("rank.txt","a");

    fprintf(f,"%s %i", nome, vitoria);
    fprintf(f, "\n");
    fclose(f);
}

// Funcao que organiza os arquivos do maior para o menor
void organizar(int* pontuacao, char nomes[10][255], int tamanho){ 
    int trocou;

    do{
        trocou = 0;

        for(int i = tamanho; i > 0; i--){   
            if (pontuacao[i] > pontuacao[i-1]){   
                int pAux;
                char nAux[255];

                pAux = pontuacao[i];

                strcpy(nAux, nomes[i]);

                pontuacao[i] = pontuacao[i-1];

                strcpy(nomes[i], nomes[i-1]);
    
                pontuacao[i-1] = pAux;

                strcpy(nomes[i-1], nAux);

                trocou = 1;
            }   
        }   
    }while(trocou);
}

// Funcao que ler o arquivo e o printa
void ranking(){         
    printf("\n ######- Ranking de Jogadores -######\n");
    printf("  \n");
    printf("NOME PONT\n");
    printf("  \n");

    FILE * pont_arq;

    pont_arq = fopen("rank.txt", "r");

    char nomes[10][255];
    int pontuacoes[10];
    char nome[255];
    int pontuacao;
    int tamanho = 0;

    while(fscanf(pont_arq, "%s   %d\n", nome, &pontuacao) != EOF){   
        strcpy(nomes[tamanho],nome);
        pontuacoes[tamanho] = pontuacao;
        tamanho++;  
    }

    organizar(pontuacoes, nomes, tamanho);

    for(int  i = 0; i < tamanho; i++){
        printf("%s %d\n", nomes[i], pontuacoes[i]);
    }

    fclose(pont_arq);
}

int gerar_posicao(int linha, int coluna){
    return (((linha *  (TAMANHO_MAX_TABULEIRO - 1)) + coluna) + (linha + 1));
}

int verifica_vitoria_horizontal(){
    int jogador_vencedor = 0;
    int contador_seguimento = 1;

    for(int i = 0; i < TAMANHO_MAX_TABULEIRO; i++){
        if(contador_seguimento == 3){
            break;
        }

        for(int j = 0; j < TAMANHO_MAX_TABULEIRO; j++){
            if(contador_seguimento == 3){
                break;
            }

            int jogador_vencedor_passado = jogador_vencedor;

            if(tabuleiro[i][j] == 'X'){
                jogador_vencedor = 8;
            }else if(tabuleiro[i][j] == 'Z'){
                jogador_vencedor = 9;
            }else{
                jogador_vencedor = 0;
            }

            if(jogador_vencedor != jogador_vencedor_passado){
                contador_seguimento = 1;
            }else{
               if(jogador_vencedor != 0){
                    contador_seguimento ++;
                }
            }
        }
    }

    if(contador_seguimento < 3){
        jogador_vencedor = 0;
    }

    return jogador_vencedor;
}

int verifica_vitoria_vertical(){
    int jogador_vencedor = 0;
    int contador_seguimento = 1;

    for(int i = 0; i < TAMANHO_MAX_TABULEIRO; i++){
        if(contador_seguimento == 3){
            break;
        }

        for(int j = 0; j < TAMANHO_MAX_TABULEIRO; j++){
            if(contador_seguimento == 3){
                break;
            }

           int jogador_vencedor_passado = jogador_vencedor;

            if(tabuleiro[j][i] == 'X'){
                jogador_vencedor = 8;
            }else if(tabuleiro[j][i] == 'Z'){
                jogador_vencedor = 9;
            }else{
                jogador_vencedor = 0;
            }

            if(contador_seguimento == 3){
                break;
            }

            if(jogador_vencedor != jogador_vencedor_passado){
                contador_seguimento = 1;
            }else{
                if(jogador_vencedor != 0){
                    contador_seguimento ++;
                }
            }
        }

        if(contador_seguimento < 3){
            jogador_vencedor = 0;
        }
    }

    return jogador_vencedor;
}

int verifica_vitoria_diagonal(){
    int jogador_vencedor = 0;
    int contador_seguimento = 1;

    for(int diagonais_buscadas = 1; diagonais_buscadas <= 2; diagonais_buscadas++){
        for(int i = 0; i < TAMANHO_MAX_TABULEIRO; i++){
            if(contador_seguimento == 3){
                break;
            }

            for(int j = 0; j < TAMANHO_MAX_TABULEIRO; j++){
                if(contador_seguimento == 3){
                    break;
                }

                if(diagonais_buscadas == 1){
                    if(i == j){
                        int jogador_vencedor_passado = jogador_vencedor;

                        if(tabuleiro[i][j] == 'X'){
                            jogador_vencedor = 8;
                        }else if(tabuleiro[i][j] == 'Z'){
                            jogador_vencedor = 9;
                        }else{
                            jogador_vencedor = 0;
                        }

                        if(jogador_vencedor != jogador_vencedor_passado){
                            contador_seguimento = 1;
                        }else{
                           if(jogador_vencedor != 0){
                                contador_seguimento ++;
                            }
                        }
                    }
                }else{
                    if(j == ((TAMANHO_MAX_TABULEIRO - 1) - i)){
                        int jogador_vencedor_passado = jogador_vencedor;

                        if(tabuleiro[i][j] == 'X'){
                            jogador_vencedor = 8;
                        }else if(tabuleiro[i][j] == 'Z'){
                            jogador_vencedor = 9;
                        }else{
                            jogador_vencedor = 0;
                        }

                        if(jogador_vencedor != jogador_vencedor_passado){
                            contador_seguimento = 1;
                        }else{
                           if(jogador_vencedor != 0){
                                contador_seguimento ++;
                            }
                        }
                    }
                }
                
            }
        }
    }

    if(contador_seguimento < 3){
        jogador_vencedor = 0;
    }

    return jogador_vencedor;
}

int main(void){
    // Declaracao de variaveis usadas
    int v_jogador1 =0; // vitorias jogador 1
    int v_jogador2 =0; // vitorias jogador 2
    int opcao = 0;     // decide se o jogo para ou nao
    char nome_jogador1[4]; // vetor com o nome do jogador1
    char nome_jogador2[4]; // vetor com o nome do jogador2

    printf("Oi, bem vind@ ao jogo da velha. Por favor, insira o nome do Player 1, com 3 letras: \n");

    // verifica o tamanho do nome, só permite que o programa prossiga se cumprir os requisitos
    int tamanho_nome = 0;

    do{
        scanf("%s%*c", nome_jogador1);
        tamanho_nome= strlen(nome_jogador1);

        if(tamanho_nome>4){
            printf("Nome invalido. Insira novamente.\n");
        }
    }while(tamanho_nome>4);

    tamanho_nome = 0 ;

    printf("Agora insira o nome do Player2: \n");
    // verifica o tamanho do nome, só permite que o programa prossiga se cumprir os requisitos
    do{
        scanf("%s%*c", nome_jogador2);

        tamanho_nome = strlen(nome_jogador2);

        //printf("%s", nome_jogador1);

        if(tamanho_nome>4){
            printf("Nome invalido. Insira novamente.\n");
        }
    }while(tamanho_nome>4);

    while(!(opcao==2)){
        // Renderiza o tabuleiro  
        for(int i = 0; i < TAMANHO_MAX_TABULEIRO; i++){
            for(int j = 0; j < TAMANHO_MAX_TABULEIRO; j++){
                tabuleiro[i][j] = gerar_posicao(i, j) + '0';
            }
        }

        // Por seguranca, zera a opcao
        opcao=0;

        printf("Bem vindos %s e %s! %s Selecione X ou O para comecar.\n", nome_jogador1, nome_jogador2, nome_jogador1);

        char simbolo1;

        simbolo1=ler_jogador();

        renderiza();
        escreve();
        renderiza();

        int velha = 0;
        int teste = 0;

        // Funcao que, olha se houve velha pelo numero de jogadas
        while(teste != 8 && velha < 8 && teste != 9){
            joga();

            teste = verifica_vitoria();

            velha++;
        }

        if((teste != 8) && (teste != 9)){
            printf("Deu velha. Ninguem pontua!");
        }

        // Teste para ver quem ganhou a partir de suas escolhas
        if ((teste == 8) && (simbolo1 == 'X')){
            v_jogador1 += 1;
        }
        if ((teste == 8) && (simbolo1 == 'O')){
            v_jogador1 += 1;
        }
        if ((teste == 9) && (simbolo1 == 'X')){
            v_jogador2 += 1;
        }
        if ((teste == 9) && (simbolo1 == 'O')){
            v_jogador2 += 1;
        }

        // Verifica com o usuario se ele deseja parar ou nao
        printf("Se desejam continuar digite [1] para continuar e [2] para finalizar o jogo:  ");
        while ((!(opcao == 2)) && (!(opcao == 1))){
            scanf("%i", &opcao);

            if((!(opcao == 2)) && (!(opcao == 1))){
                printf("Opcao invalida. Digite novamente!\n");
            }
        }
    }

    // Para evitar escrever jogadores com pontuacoes nulas, se faz esse teste
    if(v_jogador1 != 0){
        escrever_rank(nome_jogador1, v_jogador1);
    }

    if(v_jogador2 != 0){
        escrever_rank(nome_jogador2, v_jogador2);
    }

    ranking();

    return 0;
}
