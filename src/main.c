#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libtrab.h"

void lerArquivo(FILE* arquivo, thash* hash, tavl* avl_nome, tavl* avl_lat, tavl* avl_long, tavl* avl_uf, tavl* avl_ddd){
    char linha[200];
    tcidade cidade;
    titem *item;
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
            avl_insere(&avl_nome, item);
            item->tipo = 2;
            avl_insere(&avl_lat, item);
            item->tipo = 3;
            avl_insere(&avl_long, item);
            item->tipo = 4;
            avl_insere(&avl_uf, item);
            item->tipo = 5;
            avl_insere(&avl_ddd, item);
        }
    }
}

int main(){
    thash *hash = criarHash(TAM);
    tavl *avl_nome = NULL;
    tavl *avl_lat = NULL;
    tavl *avl_long = NULL;
    tavl *avl_uf = NULL;
    tavl *avl_ddd = NULL;
    FILE* arquivo = fopen("../data/municipios.json", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return EXIT_FAILURE;
    }

    lerArquivo(arquivo, hash, avl_nome, avl_lat, avl_long, avl_uf, avl_ddd);

    fclose(arquivo);
    return EXIT_SUCCESS;
}