#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    }while (trocou);
}

void ranking(){         

    //system("clear");
    printf("\n ######- Ranking de Jogadores -######\n");
    printf("  \n");
    printf("NOME PONT\n");
    printf("  \n");

    // cria ponteiro de arquivo
    FILE * pont_arq;
    //abrindo o arquivo_frase em modo "somente leitura"
    pont_arq = fopen("rank.txt", "r");
    // cria matriz para 10 nomes (poderia ser dinamico) e array de pontuações
    char nomes[10][255];
    int pontuacoes[10];
    //variaveis que irá receber o nome ea pontuação do arquivo
    char nome[255];
    int pontuacao;
    //quantidade de jogadores
    int tamanho = 0;

    //lê do arquivo
    while(fscanf(pont_arq, "%s   %d\n", nome, &pontuacao) != EOF)
    {   
        strcpy(nomes[tamanho],nome);
        pontuacoes[tamanho] = pontuacao;
        tamanho++;  
    }

    //Ordena
    organizar(pontuacoes, nomes, tamanho);

    //Imprime
    int i;
    for (i=0; i<tamanho; i++)
    {
        printf("%s %d\n", nomes[i], pontuacoes[i]);
    }

  fclose(pont_arq);
}

int main(void) {
  ranking();
  return 0;
}