#include <stdio.h>
void escrever_rank(nome){
    char* nome;
    //int pontuacao;
    FILE *f  = fopen("rank.txt","a");
    fprintf(f, "\n");
    fprintf(f,"%s", nome);
    fclose(f);
}