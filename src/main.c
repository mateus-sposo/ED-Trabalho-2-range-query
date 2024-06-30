#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libtrab.h"

char* estaAtiva(int ativas[5], int tipo){
    if(ativas[tipo-1] == 1){
        return "Ativa";
    }
    return "Inativa";
}

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
    int *ativas = (int*)calloc(5, sizeof(int));
    char queryNome[2][MAX] = {"", ""};
    double *queryLat = (double*)calloc(2, sizeof(double));
    double *queryLong = (double*)calloc(2, sizeof(double));
    int *queryUf = (int*)calloc(2, sizeof(int));
    int *queryDdd = (int*)calloc(2, sizeof(int));


    while(opcao != 8){
        printf("--------------------------------------\n");
        printf("Digite o Numero da query que deseja atualizar\n");
        printf("1 - %s - Cidade por nome -> \' %s \' - \' %s \'\n", estaAtiva(ativas, 1), queryNome[0], queryNome[1]);
        printf("2 - %s - Cidade por latitude -> %lf - %lf\n", estaAtiva(ativas, 2), queryLat[0], queryLat[1]);
        printf("3 - %s - Cidade por longitude -> %lf - %lf\n", estaAtiva(ativas, 3), queryLong[0], queryLong[1]);
        printf("4 - %s - Cidade por UF -> %d - %d\n", estaAtiva(ativas, 4), queryUf[0], queryUf[1]);
        printf("5 - %s - Cidade por DDD -> %d - %d\n", estaAtiva(ativas, 5), queryDdd[0], queryDdd[1]);
        printf("--------------------------------------\n");
        printf("6 - Desativar query\n");
        printf("7 - Realizar consulta\n");
        printf("8 - Sair\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        printf("--------------------------------------\n");
        switch(opcao){
            case 1:
                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", queryNome[0]);
                printf("Digite o nome da cidade: ");
                scanf(" %[^\n]", queryNome[1]);
                ativas[0] = 1;
                break;
            case 2:
                printf("Digite a latitude da cidade: ");
                scanf("%lf", &queryLat[0]);
                printf("Digite a latitude da cidade: ");
                scanf("%lf", &queryLat[1]);
                ativas[1] = 1;
                break;
            case 3:
                printf("Digite a longitude da cidade: ");
                scanf("%lf", &queryLong[0]);
                printf("Digite a longitude da cidade: ");
                scanf("%lf", &queryLong[1]);
                ativas[2] = 1;
                break;
            case 4:
                printf("Digite o codigo da UF: ");
                scanf("%d", &queryUf[0]);
                printf("Digite o codigo da UF: ");
                scanf("%d", &queryUf[1]);
                ativas[3] = 1;
                break;
            case 5:
                printf("Digite o DDD da cidade: ");
                scanf("%d", &queryDdd[0]);
                printf("Digite o DDD da cidade: ");
                scanf("%d", &queryDdd[1]);
                ativas[4] = 1;
                break;
            case 6:
                int desat;
                printf("Digite o número da query que deseja desativar: ");
                scanf("%d", &desat);
                ativas[desat-1] = 0;
                break;
            case 7:
                tresultado *res = (tresultado*)malloc(sizeof(tresultado));
                res->quant = 0;
                res->prox = NULL;
                if(ativas[0] == 1){
                    if(strcmp(queryNome[0], queryNome[1])>0){
                        char aux[MAX];
                        strcpy(aux, queryNome[0]);
                        strcpy(queryNome[0], queryNome[1]);
                        strcpy(queryNome[1], aux);
                    }
                    titem *aux1 = (titem*)malloc(sizeof(titem));
                    strcpy(aux1->nome, queryNome[0]);
                    aux1->tipo = 1;
                    tavl *menor = buscaMenor(&avl_nome->raiz, aux1);
                    strcpy(aux1->nome, queryNome[1]);
                    retornaIntervalo(&menor, aux1, &res);
                }
                if(ativas[1] == 1){
                    if(queryLat[0] > queryLat[1]){
                        double aux = queryLat[0];
                        queryLat[0] = queryLat[1];
                        queryLat[1] = aux;
                    }
                    titem *aux2 = (titem*)malloc(sizeof(titem));
                    aux2->latitude = queryLat[0];
                    aux2->tipo = 2;
                    tavl *menor = buscaMenor(&avl_lat->raiz, aux2);
                    aux2->latitude = queryLat[1];
                    retornaIntervalo(&menor, aux2, &res);
                }
                if(ativas[2] == 1){
                    if(queryLong[0] > queryLong[1]){
                        double aux = queryLong[0];
                        queryLong[0] = queryLong[1];
                        queryLong[1] = aux;
                    }
                    titem *aux3 = (titem*)malloc(sizeof(titem));
                    aux3->longitude = queryLong[0];
                    aux3->tipo = 3;
                    tavl *menor = buscaMenor(&avl_long->raiz, aux3);
                    aux3->longitude = queryLong[1];
                    retornaIntervalo(&menor, aux3, &res);
                }
                if(ativas[3] == 1){
                    if(queryUf[0] > queryUf[1]){
                        int aux = queryUf[0];
                        queryUf[0] = queryUf[1];
                        queryUf[1] = aux;
                    }
                    titem *aux4 = (titem*)malloc(sizeof(titem));
                    aux4->codigo_uf = queryUf[0];
                    aux4->tipo = 4;
                    tavl *menor = buscaMenor(&avl_uf->raiz, aux4);
                    aux4->codigo_uf = queryUf[1];
                    retornaIntervalo(&menor, aux4, &res);
                }
                if(ativas[4] == 1){
                    if(queryDdd[0] > queryDdd[1]){
                        int aux = queryDdd[0];
                        queryDdd[0] = queryDdd[1];
                        queryDdd[1] = aux;
                    }
                    titem *aux5 = (titem*)malloc(sizeof(titem));
                    aux5->ddd = queryDdd[0];
                    aux5->tipo = 5;
                    tavl *menor = buscaMenor(&avl_ddd->raiz, aux5);
                    aux5->ddd = queryDdd[1];
                    retornaIntervalo(&menor, aux5, &res);
                }
                int qntAtivas = 0;
                for(int i = 0; i < 5; i++){
                    if(ativas[i] == 1){
                        qntAtivas++;
                    }
                }
                tresultado *aux = res;
                while(aux != NULL){
                    if(aux->quant == qntAtivas){
                        printf("Codigo IBGE: %d\n", aux->codigo);
                    }
                    aux = aux->prox;
                }
                break;
            case 8:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
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