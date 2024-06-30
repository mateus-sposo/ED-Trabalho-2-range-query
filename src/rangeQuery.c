#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libtrab.h"

tavl * buscaMenor(tavl ** avl, titem *itemMenor){
    if(*avl == NULL){
        return NULL;
    }
    if(compara((*avl)->item, itemMenor) >= 0){
        tavl *aux = buscaMenor(&(*avl)->dir, itemMenor);
        if(aux != NULL){
            return aux;
        }
        return *avl;
    }
    return buscaMenor(&(*avl)->dir, itemMenor);
}

void retornaIntervalo(tavl ** avl, titem *itemMaior, tresultado ** res){
    if(*avl == NULL || compara((*avl)->item, itemMaior) > 0){
        return;
    }
    if(compara((*avl)->item, itemMaior) <= 0){
        titem *aux = (*avl)->item;
        while(aux != NULL){
            insereListaRes(res, (*avl)->item->codigo_ibge);
            aux = aux->prox;
        }
        avl = procura_sucessor(avl);
        retornaIntervalo(avl, itemMaior, res);
    }
}