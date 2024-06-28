#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libtrab.h"

void lerArquivo(FILE* arquivo, tavl* arvore){
    char linha[200];
    tcidade cidade;
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
            
        }
    }
}

int main(){
    FILE* arquivo = fopen("../dados/municipios.json", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return EXIT_FAILURE;
    }

    lerArquivo(arquivo, NULL);

    interface();

    fclose(arquivo);
    return EXIT_SUCCESS;
}