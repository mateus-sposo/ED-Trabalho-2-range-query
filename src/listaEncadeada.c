#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libtrab.h"

void insereLista(titem ** lista, titem *item){
    titem *aux = *lista;
    if(*lista == NULL){
        *lista = (titem*)malloc(sizeof(titem));
        (*lista)->codigo_ibge = item->codigo_ibge;
        strcpy((*lista)->nome, item->nome);
        (*lista)->latitude = item->latitude;
        (*lista)->longitude = item->longitude;
        (*lista)->codigo_uf = item->codigo_uf;
        (*lista)->ddd = item->ddd;
        (*lista)->tipo = item->tipo;
        (*lista)->prox = NULL;
    }
    else{
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = (titem*)malloc(sizeof(titem));
        aux->prox->codigo_ibge = item->codigo_ibge;
        strcpy(aux->prox->nome, item->nome);
        aux->prox->latitude = item->latitude;
        aux->prox->longitude = item->longitude;
        aux->prox->codigo_uf = item->codigo_uf;
        aux->prox->ddd = item->ddd;
        aux->prox->tipo = item->tipo;
        aux->prox->prox = NULL;
    }
}

void insereListaRes(tresultado ** lista, int codigo){
    tresultado *aux = *lista;
    if(*lista == NULL){
        *lista = (tresultado*)malloc(sizeof(tresultado));
        (*lista)->codigo = codigo;
        (*lista)->quant = 1;
        (*lista)->prox = NULL;
    }
    else{
        while(aux->prox != NULL){
            if(aux->codigo == codigo){
                aux->quant += 1;
                return;
            }
            aux = aux->prox;
        }
        aux->prox = (tresultado*)malloc(sizeof(tresultado));
        aux->prox->codigo = codigo;
        aux->prox->quant = 1;
        aux->prox->prox = NULL;
    }
}

void destroiLista(titem ** lista){
    titem *aux = *lista;
    if(aux->prox != NULL)
        destroiLista(&aux->prox);
    free(aux);
}

void destroiListaRes(tresultado ** lista){
    tresultado *aux = *lista;
    if(aux->prox != NULL)
        destroiListaRes(&aux->prox);
    free(aux);
}