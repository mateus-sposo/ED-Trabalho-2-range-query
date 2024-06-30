#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libtrab.h"

void lerArquivo(FILE* arquivo, thash* hash, traiz* avl_nome, traiz* avl_lat, traiz* avl_long, traiz* avl_uf, traiz* avl_ddd){
    char linha[200];
    tcidade cidade;
    titem *item = (titem*)malloc(sizeof(titem));
    while(fgets(linha, 200, arquivo)){
        if(strstr(linha, "codigo_ibge")){
            sscanf(linha, "    \"codigo_ibge\": %d,", &cidade.codigo_ibge);
        }
        if(strstr(linha, "nome")){
            sscanf(linha, "    \"nome\": \"%[^\"]\",", cidade.nome);
        }
        if(strstr(linha, "latitude")){
            sscanf(linha, "    \"latitude\": %lf,", &cidade.latitude);
        }
        if(strstr(linha, "longitude")){
            sscanf(linha, "    \"longitude\": %lf,", &cidade.longitude);
        }
        if(strstr(linha, "capital")){
            sscanf(linha, "    \"capital\": %hhd,", &cidade.capital);
        }
        if(strstr(linha, "codigo_uf")){
            sscanf(linha, "    \"codigo_uf\": %hd,", &cidade.codigo_uf);
        }
        if(strstr(linha, "siafi_id")){
            sscanf(linha, "    \"siafi_id\": %hd,", &cidade.siafi_id);
        }
        if(strstr(linha, "ddd")){
            sscanf(linha, "    \"ddd\": %hd,", &cidade.ddd);
        }
        if(strstr(linha, "fuso_horario")){
            sscanf(linha, "    \"fuso_horario\": \"%[^\"]\",", cidade.fuso_horario);
            insereHash(hash , cidade);

            item->codigo_ibge = cidade.codigo_ibge;
            strcpy(item->nome, cidade.nome);
            item->latitude = cidade.latitude;
            item->longitude = cidade.longitude;
            item->codigo_uf = cidade.codigo_uf;
            item->ddd = cidade.ddd;

            item->tipo = 1;
            avl_insere(avl_nome, item);
            item->tipo = 2;
            avl_insere(avl_lat, item);
            item->tipo = 3;
            avl_insere(avl_long, item);
            item->tipo = 4;
            avl_insere(avl_uf, item);
            item->tipo = 5;
            avl_insere(avl_ddd, item);
        }
    }
}

void interface(thash *hash_cod, traiz *avl_nome, traiz *avl_lat, traiz *avl_long, traiz *avl_uf, traiz *avl_ddd){
    int opcao = 0;
    char[2] queryNome[MAX];
    double[2] queryLat;
    double[2] queryLong;
    int[2] queryUf;
    int[2] queryDdd;

    while(opcao != 4){
        printf("--------------------------------------\n");
        printf("Digite o Númro da query que deseja atualizar\n");
        printf("1 - Cidade por nome -> \' %s \' - \' %s \'\n", queryNome[0], queryNome[1]);
        printf("2 - Cidade por latitude -> %lf - %lf\n", queryLat[0], queryLat[1]);
        printf("3 - Cidade por longitude -> %lf - %lf\n", queryLong[0], queryLong[1]);
        printf("4 - Cidade por UF -> %d - %d\n", queryUf[0], queryUf[1]);
        printf("5 - Cidade por DDD -> %d - %d\n", queryDdd[0], queryDdd[1]);
        printf("--------------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("--------------------------------------\n");
        switch(opcao){
        }
    }
}

// void imprimeAVL(tavl *avl){
//     if(avl != NULL){
//         imprimeAVL(avl->esq);
//         titem *aux = avl->item;
//         while(aux != NULL){
//             printf("%s\n", aux->nome);
//             aux = aux->prox;
//         }
//         imprimeAVL(avl->dir);
//     }
// }

int main(){
    thash *hash = criarHash(TAM);
    traiz avl_nome, avl_lat, avl_long, avl_uf, avl_ddd;
    avl_nome.raiz = NULL;
    avl_lat.raiz = NULL;
    avl_long.raiz = NULL;
    avl_uf.raiz = NULL;
    avl_ddd.raiz = NULL;
    FILE* arquivo = fopen("../data/municipios.json", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return EXIT_FAILURE;
    }
    lerArquivo(arquivo, hash, &avl_nome, &avl_lat, &avl_long, &avl_uf, &avl_ddd);
    interface(hash, &avl_nome, &avl_lat, &avl_long, &avl_uf, &avl_ddd);

    fclose(arquivo);
    return EXIT_SUCCESS;
}