// Declaração de Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAX_MAPA 3

void escreve(void);
void renderiza(void);
char ler_jogador(void);
int verifica_vitoria(void);
void joga(void);
void escrever_rank(char nome[4], int vitoria);
void organizar(int* pontuacao, char nomes[10][255], int tamanho);
void ranking();

// Variaveis Globais
char Mapa [TAMANHO_MAX_MAPA][TAMANHO_MAX_MAPA];
char jogador = ' ';

// Declaração de Funcoes
// Funcao que escreve no mapa do jogo da velha
void escreve(void){
    int ocupado = 0;

    while(ocupado == 0){
        int posicao = 0;

        printf("Selecione uma posicao: \n");
        scanf("%i", &posicao);

        switch (posicao){
            case 1:
                if(Mapa[0][0] == 'X' || Mapa[0][0] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra.\n");
                }else{
                    Mapa [0][0] = jogador;
                    ocupado = 1;
                }

                break;

            case 2:
                if(Mapa[0][1] == 'X' || Mapa[0][1] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra\n");
                }else{
                    Mapa [0][1] = jogador;
                    ocupado = 1;
                }

                break;

            case 3:
                if(Mapa[0][2] == 'X' || Mapa[0][2] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra\n");
                }else{
                    Mapa [0][2] = jogador;
                    ocupado = 1;
                }

                break;

            case 4:
                if(Mapa[1][0] == 'X' || Mapa[1][0] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra\n");
                }else{
                    Mapa [1][0] = jogador;
                    ocupado = 1;
                }

                break;

            case 5:
                if(Mapa[1][1] == 'X' || Mapa[1][1] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra\n");
                }else{
                    Mapa [1][1] = jogador;
                    ocupado = 1;
                }

                break;

            case 6:
                if(Mapa[1][2] == 'X' || Mapa[1][2] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra\n");
                }else{
                    Mapa [1][2] = jogador;
                    ocupado = 1;
                }

                break;

            case 7:
                if(Mapa[2][0] == 'X' || Mapa[2][0] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra\n");
                }else{
                    Mapa [2][0] = jogador;
                    ocupado = 1;
                }

                break;

            case 8:
                if(Mapa[2][1] == 'X' || Mapa[2][1] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra\n");
                }else{
                    Mapa [2][1] = jogador;
                    ocupado = 1;
                }

                break;

            case 9:
                if(Mapa[2][2] == 'X' || Mapa[2][2] == 'O'){
                    printf("Posição ocupada. Por favor, escolha outra\n");
                }else{
                    Mapa [2][2] = jogador;
                    ocupado = 1;
                }

                break;
        }
    }
}

// Funcao que renderiza o mapa.
void renderiza(void){
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            printf("%c ", Mapa[i][j]);
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

    for (int i = 0; i < 3; i++){
        if (Mapa[i][0] == Mapa[i][1] && Mapa[i][0] == Mapa[i][2]){
            if (Mapa[i][0] == 'X'){
                i = 3;
                venceu = 8;
            }else{
                i = 3;
                venceu = 9;
            }
        }
    }

    for (int i = 0; i < 3; i++){
        if (Mapa[0][i] == Mapa[1][i] && Mapa[0][i] == Mapa[2][i]){
            if (Mapa[0][i] == 'X'){
                i = 3;
                venceu = 8;
            }else{
                i = 3;
                venceu = 9;
            }
        }
    }

    if(Mapa[0][2]==Mapa[1][1]&&Mapa[0][2]==Mapa[2][0]){
        if (Mapa[0][2] == 'X'){
            venceu = 8;
        }else{
            venceu = 9;
        }
    }

    if(Mapa[0][0] == Mapa[1][1] && Mapa[0][0] == Mapa[2][2]){
        if (Mapa[0][2] == 'X'){
            venceu = 8;
        }else{
            venceu = 9;
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
    int i;
    int trocou;

    do{
        trocou = 0;

        for (i=tamanho; i > 0; i--){   
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

    for (int  i=0; i<tamanho; i++){
        printf("%s %d\n", nomes[i], pontuacoes[i]);
    }

    fclose(pont_arq);
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
        // Renderiza o mapa  
        for(int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                Mapa[i][j] = (((i *  (TAMANHO_MAX_MAPA - 1)) + j) + (i + 1)) + '0';
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
        while(teste!=8 && velha < 8 && teste!=9){
            joga();

            teste = verifica_vitoria();

            velha++;
        }

        if((teste!=8)&&(teste!=9)){
            printf("Deu velha. Ninguem pontua!");
        }

        // Teste para ver quem ganhou a partir de suas escolhas
        if ((teste==8)&&(simbolo1=='X')){
            v_jogador1 += 1;
        }
        if ((teste==8)&&(simbolo1=='O')){
            v_jogador1 += 1;
        }
        if ((teste==9)&&(simbolo1=='X')){
            v_jogador2 += 1;
        }
        if ((teste==9)&&(simbolo1=='O')){
            v_jogador2 += 1;
        }

        // Verifica com o usuario se ele deseja parar ou nao
        printf("Se desejam continuar digite [1] para continuar e [2] para finalizar o jogo:  ");
        while ((!(opcao==2))&&(!(opcao==1))){
            scanf("%i", &opcao);

            if((!(opcao==2))&&(!(opcao==1))){
                printf("Opcao invalida. Digite novamente!\n");
            }
        }
    }

    // Para evitar escrever jogadores com pontuacoes nulas, se faz esse teste
    if(v_jogador1!=0){
        escrever_rank(nome_jogador1, v_jogador1);
    }

    if(v_jogador2!=0){
        escrever_rank(nome_jogador2, v_jogador2);
    }

    ranking();

    return 0;
}
