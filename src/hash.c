#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/libtrab.h"

thash* criarHash(int tamanho){
    thash *hash = (thash*)malloc(sizeof(thash));
    hash->tamanho = tamanho;
    hash->cidades = (tcidade*)malloc(tamanho*sizeof(tcidade)+1);
    for(int i=0; i <= tamanho; i++){
        hash->cidades[i].codigo_ibge = 0;
    }
    return hash;
}

void insereHash(thash *hash, tcidade cidade){
    int i = 0;
    int pos; 
    while(1){
        pos = (h1(cidade.codigo_ibge, hash->tamanho) + i * h2(cidade.codigo_ibge, hash->tamanho)) % hash->tamanho;
        if(hash->cidades[pos].codigo_ibge == 0){
            hash->cidades[pos] = cidade;
            hash->atual += 1;
            break;
        }
        i++;
    }
}

void liberaHash(thash* hash){
    free(hash->cidades);
    free(hash);
}

int h1(int codigo_ibge, int tamanho){
    return (codigo_ibge) % tamanho;
}

int h2(int codigo_ibge, int tamanho){
    return 1 + (codigo_ibge) % (tamanho - 1);
}

tcidade buscaIBGE(thash* hash, int codigo_ibge){
    int i = 0;
    int pos = h1(codigo_ibge, hash->tamanho);
    while(1){
        if(hash->cidades[pos].codigo_ibge == codigo_ibge){
            return hash->cidades[pos];
        }
        if(i > hash->tamanho){
            tcidade falsa;
            falsa.codigo_ibge = 0;
            return falsa;
        }
        i++;
        pos = (h1(codigo_ibge, hash->tamanho) + i * h2(codigo_ibge, hash->tamanho)) % hash->tamanho;
    }
    return hash->cidades[pos];
}