#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libtrab.h"

void insereLista(titem **lista, titem *item){
    titem *aux = *lista;
    if(*lista == NULL){
        *lista = (titem*)malloc(sizeof(titem));
        *lista = item;
        (*lista)->prox = NULL;
    }
    else{
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = (titem*)malloc(sizeof(titem));
        aux->prox = item;
        aux->prox->prox = NULL;
    }
}

void destroiLista(titem **lista){
    titem *aux = *lista;
    if(aux->prox != NULL)
        destroiLista(&aux->prox);
    free(aux);
}