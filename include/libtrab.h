#ifndef __LIBTRAB_H__
#define __LIBTRAB_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef void* titem;

typedef struct _cidade{
    int codigo_ibge;
    char nome[MAX];
    double latitude;
    double longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char fuso_horario[MAX];
}tcidade;

typedef struct _avl{
	titem item;
    tcidade cidade;

    struct _node *pai;
	struct _node *esq;
	struct _node *dir;
	int h;
}tavl;

void lerArquivo(FILE* arquivo, tavl* arvore);
void interface();


#endif